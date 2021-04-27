# include <iostream>
# include <vector>
# include <string>
# include <sstream>
# include <string.h>
# include <vector>
# include <stdlib.h>
# include <stdio.h>
using namespace std ;

struct Token_data {
  string data  ;
  string type  ;  // math 
  string use   ;
  string count ; 
  int th    ;
} ;

struct V_ble {
  string type  ;
  string data  ;  // math 
  string array ;
} ;

int g_right_quote = 0 ;  

bool g_void = false; 
bool g_if = false; 
bool g_in_if = false ; 
string g_type  ; 
string g_data  ; 
string g_array  ; 

vector<V_ble> g_count_if ; // 在if.while.do裡面的 
vector<string> g_tp ; 


int g_func_rest = 0 ; // 判斷是FUNCTION或者REST 1為FCUN 2為REST 
string g_func_name ; // 本題變數名稱
vector<string> g_count ;
vector<string> g_count_small ;
vector<string> g_small ; // 空的 
vector< vector<string> > g_count_ready ;
vector< vector<string> > g_name_list ; 
vector< vector<string> > g_func_list ;  
int g_c = 0 ; // g_count_ready用 


// vector< vector<string> > g_func_list ; 

 
vector<Token_data> g_scan ; 
vector<string> g_name_in_all ;
vector<string> g_aldef ;


bool g_aldef_func_bool = false ; // function 只會存一次 

vector< vector<string> > g_temp ; // list all variable
vector<string> g_name ; 

bool g_al_defined = false ; 


int g_ans ; 
int g_th ;  
int g_at = 0 ; 
int g_og = 0 ; 
int g_line = 1 ; 
char g_topic[5000] ;
string g_list ; 

int g_ds = 0 ;  // definition or statement 

bool g_ui = false ; 

char g_error_char = '\0' ;
bool g_first_token = false ; 
bool g_error_1 = false ; 
bool g_error_2 = false ; 
bool g_error_3 = false ; 


bool Type_specifier( string s ) ;
bool Check_defined( string s ) ;
void User_input() ;
void Definition() ;
bool Type_specifier() ;
void Function_definition_or_declarators() ;
void Rest_of_declarators() ;
void Function_definition_without_ID() ; 
void Formal_parameter_list() ;
void Compound_statement() ;
void Declaration() ;
void Statement() ;   
void Expression() ;
void Basic_expression() ; 
void Rest_of_Identifier_started_basic_exp() ;
void Rest_of_PPMM_Identifier_started_basic_exp() ;
bool Sign() ; 
void Actual_parameter_list() ; 
bool Assignment_operator() ;  
void Romce_and_romloe() ;
void Rest_of_maybe_logical_OR_exp() ;
void Maybe_logical_AND_exp() ;
void Rest_of_maybe_logical_AND_exp() ;
void Maybe_bit_OR_exp() ; 
void Rest_of_maybe_bit_OR_exp() ;
void Maybe_bit_ex_OR_exp() ;  
void Rest_of_maybe_bit_ex_OR_exp() ;
void Maybe_bit_AND_exp() ;
void Rest_of_maybe_bit_AND_exp() ;
void Maybe_equality_exp() ;
void Rest_of_maybe_equality_exp() ; 
void Maybe_relational_exp() ;  
void Rest_of_maybe_relational_exp() ;
void Maybe_shift_exp() ;
void Rest_of_maybe_shift_exp() ;
void Maybe_additive_exp() ; 
void Rest_of_maybe_additive_exp() ;
void Maybe_mult_exp() ; 
void Rest_of_maybe_mult_exp() ;
void Unary_exp() ;
void Signed_unary_exp() ; 
void Unsigned_unary_exp() ; 
void Save_if() ;

void Save_and_clear_temp() {
  V_ble v_ble ; 
  v_ble.type = g_type ; 
  v_ble.data = g_data ; 
  v_ble.array = g_array ; 
  g_count_if.push_back( v_ble ) ; 
  v_ble = V_ble() ;  
  string g_data = "" ; 
  string g_array = "" ; 
} // Save_and_clear_temp()


// ----------------get_token_strart--------------------
void Math_take( Token_data &token, char &temp, char &next_temp ) {

  bool is_float = false; 
  bool already_float = false ; 
  token.data = token.data + g_topic[g_at] ; // 先家第一個數字 
  
  while ( ( g_topic[g_at+1] >= 48 && g_topic[g_at+1] <= 57 ) || g_topic[g_at+1] == '.' ) {
    
    if ( g_topic[g_at+1] == '.'  ) {   // 一串TOKEN只能有一個浮點數 
      if ( is_float == true )     // 報錯跳出 
        return ; 
      if ( is_float == false ) {  // 正常執行 
        is_float = true ; 
      } // if()
    } // if()
    
    token.data = token.data + g_topic[g_at+1] ;  
    g_at++;

  } // while()
} // Math_take()

void English_start( Token_data &token, char &temp, char &next_temp ) {
  bool jump = false ; 
  token.data = token.data + g_topic[g_at] ;
  while ( ( ( g_topic[g_at+1] >= 65 && g_topic[g_at+1] <= 90 )    // 為數字或者英文
            || ( g_topic[g_at+1] >= 97 && g_topic[g_at+1] <= 122 ) 
            || ( g_topic[g_at+1] >= 48 && g_topic[g_at+1] <= 57 ) 
            || ( g_topic[g_at+1] == '_' )   ) && jump == false ) {  
    token.data = token.data + g_topic[g_at+1] ; 
    g_at++;
    // if ( temp == ' ' ) break ; 
    if  ( ( g_topic[g_at+1] >= 65 && g_topic[g_at+1] <= 90 ) 
          || ( g_topic[g_at+1] >= 97 && g_topic[g_at+1] <= 122 ) 
          || ( g_topic[g_at+1] >= 48 && g_topic[g_at+1] <= 59 ) 
          || g_topic[g_at+1] == '_' || ( g_topic[g_at+1] == ':' ) ) 
    {
         
    } // if() 
    else {
      jump = true ; 
    } // else() 
  } // while()
} // English_start()

void Dot_first(  Token_data &token, char &temp, char &next_temp ) {
  
  token.type = "constant" ;  
  token.data = g_topic[g_at-1] + token.data +g_topic[g_at] ; 
  
  while ( g_topic[g_at+1] >= 48 && g_topic[g_at+1] <= 57 ) {
    g_at++;
    token.data = token.data + g_topic[g_at] ; 
  } // while()
  
} // Dot_first()

void Get_token( Token_data &token, char &temp, char &next_temp, bool &at_next ) { 
  if ( at_next == false ) {
    g_at++;
    while ( g_topic[g_at] == ' ' ) g_at++ ; 
  } // if()
  else at_next = false ; 
  // 純數字 或 小數 
  while ( g_topic[g_at] == ' ' ) g_at++ ;
  
  // 
  if ( g_topic[g_at] == '/' ) { 
    if ( g_topic[g_at+1] == '/' ) {
      while ( g_topic[g_at] != '\n' ) {
        g_at++; 
      } // while()
      
      token.data = "\n";
      return ; 
    } // if()
  } // if()
  // 數字 
  if ( g_topic[g_at] >= 48 && g_topic[g_at] <= 57 ) { 
    Math_take( token, temp, next_temp ) ;
    token.type = "constant" ;  
  } // if()
  // 小數點開頭 
  else if ( g_topic[g_at] == '.' ) { 
    if ( g_topic[g_at+1] >= 48 && g_topic[g_at+1] <= 57 ) {
      g_at++; // 讀到小數點後第一個數字 
      Dot_first( token, temp, next_temp ) ;
      token.type = "constant" ; 
    } // if()
    else {
      temp = '\0' ; 
    } // else()
  } // else if()
  
  // "" 或 ''
  else if ( g_topic[g_at] == '\"'  ||  g_topic[g_at] == '\''  ) { 
    if ( g_topic[g_at] == '\"' ) {
      while ( g_topic[g_at+1] != '\"' ) {
        token.data = token.data + g_topic[g_at] ; 
        g_at++ ; 
      } // while()
      
      token.data = token.data + g_topic[g_at] ; 
      token.data = token.data + '\"' ; 
      g_at++ ; 
    } // if()
    else if ( g_topic[g_at] == '\'' ) {
      while ( g_topic[g_at+1] != '\'' ) {
        token.data = token.data + g_topic[g_at] ; 
        g_at++ ; 
      } // while()
      
      token.data = token.data + g_topic[g_at] ; 
      token.data = token.data + '\'' ; 
      g_at++ ; 
    } // if()
    
    token.type = "constant" ; 
  } // else if()
  
  // 符號+-*/
  else if ( g_topic[g_at] == '*' || g_topic[g_at] == '/' || 
            g_topic[g_at] == '+' || g_topic[g_at] == '-' || 
            g_topic[g_at] == '%' ) {
    token.data = token.data + g_topic[g_at] ; 
    if ( g_topic[g_at] == '*' || g_topic[g_at] == '/' || g_topic[g_at] == '%' ) {
      if ( g_topic[g_at + 1] == '=' ) 
        token.data = token.data + g_topic[g_at+1] ;
      if ( token.data == "*=" ) token.type = "TE" ; 
      else if ( token.data == "/=" ) token.type = "DE" ;
      else if ( token.data == "%=" ) token.type = "RE" ;
      else token.type = "term" ;
    } // if()
    else if ( g_topic[g_at] == '+' || g_topic[g_at] == '-' ) {
      
      if ( g_topic[g_at] == '+' && g_topic[g_at+1] == '-' ) return ; 
      if ( g_topic[g_at] == '-' && g_topic[g_at+1] == '+' ) return ; 
      
      if ( g_topic[g_at + 1] == '+' || g_topic[g_at + 1] == '-' ||  g_topic[g_at + 1] == '=' ) 
        token.data = token.data + g_topic[g_at+1] ;
      if ( token.data == "+=" ) token.type = "PE" ; 
      else if ( token.data == "-=" ) token.type = "ME" ;
      else if ( token.data == "++" ) token.type = "PP" ;
      else if ( token.data == "--" ) token.type = "MM" ;
      else token.type = "sign" ; 
    } // else if()
    
    if ( token.data.size() > 1 ) g_at++ ;  
  } // else if()
  
  // 英文 
  else if ( ( g_topic[g_at] >= 65 && g_topic[g_at] <= 90 ) ||
            ( g_topic[g_at] >= 97 && g_topic[g_at] <= 122 ) ) {
    English_start( token, temp, next_temp ) ; 
    token.type = "IDENT" ; 
    if ( token.data == "int" || token.data == "char" || token.data == "float" || 
         token.data == "string" || token.data == "bool" || token.data == "void" || 
         token.data == "if" || token.data == "while" || token.data == "else" || 
         token.data == "do" || token.data == "return" )
      token.type = "IDENT2" ; 
    if ( token.data == "true" || token.data == "false" )
      token.type = "constant" ; 
  } // else if()
  
  // boolean  '=' | '<>' | '>' | '<' | '>=' | '<='
  else if ( g_topic[g_at] == '<' || g_topic[g_at] == '>' ) { 
    token.data = token.data + g_topic[g_at] ; 
    token.type = "boolean" ; 
    
    if ( g_topic[g_at] == '>' || g_topic[g_at] == '<' ) {
      

      if ( g_topic[g_at] == '>' && g_topic[g_at+1] == '=' ) 
        token.data = ">=", token.type = "GE" ; 
      else if ( g_topic[g_at] == '<' && g_topic[g_at+1] == '=' )
        token.data = "<=", token.type = "LE" ;
      else if ( g_topic[g_at] == '<' && g_topic[g_at+1] == '<' )
        token.data = "<<", token.type = "LS"  ;
      else if ( g_topic[g_at] == '>' && g_topic[g_at+1] == '>' )
        token.data = ">>", token.type = "RS"  ;
              
      if ( token.data.size() > 1 )  g_at++ ;  
    } // if()
  } // else if() 
  // &&,||
  else if ( g_topic[g_at] == '&' || g_topic[g_at] == '|' ) { 
    token.data = token.data + g_topic[g_at] ; 
    if ( g_topic[g_at] == '&' && g_topic[g_at+1] == '&' ) {
      token.data = "&&" ;
      token.type = "AND" ;
    } // if()
    else if ( g_topic[g_at] == '|' && g_topic[g_at+1] == '|' ) {
      token.data = "||" ; 
      token.type = "OR" ;
    } // else if()
    
    if ( token.data.size() > 1 )  g_at++ ;  
  } // else if() 
  // statement =/==
  else if ( g_topic[g_at] == '=' ) { 
    if ( g_topic[g_at] == '=' && g_topic[g_at+1] == '=' ) {
      token.data = "==" ;
      token.type = "EQ" ; 
      g_at++ ;  
    } // if()
    else if ( g_topic[g_at] == '=' && g_topic[g_at+1] != '=' ) {
    
      token.data = "=" ; 
      token.type = "boolean" ; 
    } // else if()
  } // else if() 
  // !=/!
  
  else if ( g_topic[g_at] == '!' ) { 
    if ( g_topic[g_at] == '!' && g_topic[g_at+1] == '=' ) {
      token.data = "!=" ;
      token.type = "NEQ" ;
      g_at++ ;  
    } // if()
    else if ( g_topic[g_at] == '!' && g_topic[g_at+1] != '=' ) 
      token.data = "!" ; 
    token.type = "!" ; 
  } // else if() 
  // ; 
  else if ( g_topic[g_at] == ';' ) {
    token.data = ";" ; 
    token.type = "statement" ; 
  } // else if() 
  // ()
  else if ( g_topic[g_at] == ')' ) { 
    token.data = ")" ; 
    token.type = "bracket_right" ; 
  } // else if() 
  else if ( g_topic[g_at] == '(' ) { 
    token.data = "(" ; 
    token.type = "bracket_left" ; 
  } // else if() 
  
  else if ( g_topic[g_at] == ']' ) { 
    token.data = "]" ; 
    token.type = "bracket_right" ; 
  } // else if() 
  else if ( g_topic[g_at] == '[' ) { 
    token.data = "[" ; 
    token.type = "bracket_left" ; 
  } // else if()
  
  else if ( g_topic[g_at] == '}' ) { 
    token.data = "}" ; 
    token.type = "bracket_right" ; 
  } // else if() 
  else if ( g_topic[g_at] == '{' ) { 
    token.data = "{" ; 
    token.type = "bracket_left" ; 
  } // else if()
   
  else if ( g_topic[g_at] == '^' ) { 
    token.data = "^" ; 
    token.type = "^" ; 
  } // else if()
  else if ( g_topic[g_at] == ',' ) { 
    token.data = "," ; 
    token.type = "," ; 
  } // else if()
  else if ( g_topic[g_at] == '?' ) { 
    token.data = "?" ; 
    token.type = "?" ; 
  } // else if()
  else if ( g_topic[g_at] == ':' ) { 
    token.data = ":" ; 
    token.type = ":" ; 
  } // else if()
  
  else if ( g_topic[g_at] == '\n' ) {
    token.data = "\n" ; 
    token.type = "next_line" ; 
  } // else if()
  else if ( g_topic[g_at] == ' ' ) {
    token.data = " " ; 
    token.type = " " ; 
  } // else if()
  else {
    
    if ( g_error_1 == false ) g_error_char = g_topic[g_at] ; 
    token.data = g_topic[g_at] ; 
    token.type = "not_define" ; 
    g_error_1 = true; 
    
  } // else() 
  
  return;
} // Get_token()

// -------------scanner---------------

void Go_back() {
  if ( g_error_2 == false ) {
    if ( g_scan.at( g_og ).data == "\n" )
      g_scan.at( g_og ).count = "" ;
    
    
    g_th = g_og ;
  
  } // if()
} // Go_back()

void Save_token() {
  if ( g_scan.at( g_th ).use != "used" )  { // 存 token 
  
    if ( g_scan.at( g_th ).data == "\n" ) {
      g_scan.at( g_th ).use = "used" ;
      return; 
    } // if()
    else {
      g_name.push_back( g_scan.at( g_th ).data ) ; 
      g_list = g_list + g_scan.at( g_th ).data ;
    } // else()
  } // if()
  
  g_scan.at( g_th ).use = "used" ; 
  
} // Save_token()

bool S_defined() { 
  if ( g_scan.at( g_th ).data != "void" && g_scan.at( g_th ).data != "int" && 
       g_scan.at( g_th ).data != "char" && g_scan.at( g_th ).data != "float" && 
       g_scan.at( g_th ).data != "string" && g_scan.at( g_th ).data != "bool"  ) {
    if ( ( g_ds == 2  ) && g_scan.at( g_th ).type == "IDENT" && 
         Type_specifier( g_scan.at( g_og ).data ) == false ) {
      bool check = false ; 
      
      // cout << "***" << g_scan.at( g_th ).data << endl ; 
      
      for ( int i = 0 ; i < g_aldef.size() ; i++ ) {  // 檢查是否曾經存過 函數名稱 EX:cin . cout  
        if ( g_scan.at( g_th ).data == g_aldef.at( i ) ) 
          check = true ;  
          // cout << "++" << endl; 
      } // for()
      
      for ( int i = 0 ; i < g_func_list.size() ; i++ ) {  // 檢查是否曾經存過 函數名字  
        if ( g_scan.at( g_th ).data == g_func_list.at( i ).at( 1 ) ) 
          check = true ;  
          // cout << "++" << endl; 
      } // for()
      
      for ( int i = 0 ; i < g_count_small.size() ; i++ ) {  // 檢查是否曾經存過  區域變數 
        if ( g_scan.at( g_th ).data == g_count_small.at( i ) ) 
          check = true ;  
          // cout << "++" << endl; 
      } // for()
      
      for ( int k = 0 ; k < g_count_ready.size() ; k++ ) {
        for ( int i = 0 ; i < g_count_ready.at( k ).size() ; i++ ) {  // 檢查是否曾經存過  大區域變數 
          if ( g_scan.at( g_th ).data == g_count_ready.at( k ).at( i ) ) 
            check = true ;  
          // cout << "++" << endl; 
        } // for()
      } // for()
      
      for ( int i = 0 ; i < g_name_list.size() ; i++ ) {  // 檢查是否曾經存過  全域變數 
        if ( g_scan.at( g_th ).data == g_name_list.at( i ).at( 1 ) ) 
          check = true ;  
          // cout << "--" << endl ; 
      } // for()
      
      for ( int i = 0 ; i < g_func_list.size() ; i++ ) {  // 檢查是否曾經存過  全域變數 
        if ( g_scan.at( g_th ).data == g_func_list.at( i ).at( 1 ) ) 
          check = true ;  
          // cout << "--" << endl ; 
      } // for()
      
      if ( check == false ) { // 若從未存過 
        g_error_2 = true ; 
        g_error_3 = true ;
        // cout << "沒有存過" << g_scan.at( g_th ).data << endl ; 
        return false ; 
      } // if()
      else {
        return true ; 
      } // else()
      
    } // if()
  } // if()
  
  return true ; 
} // S_defined()

void Get_next_token() { 
  if ( g_first_token == false ) {  
    g_first_token = true ; 
    if ( g_scan.at( g_th ).data == "void" || g_scan.at( g_th ).data == "int" || 
         g_scan.at( g_th ).data == "char" || g_scan.at( g_th ).data == "float" || 
         g_scan.at( g_th ).data == "string" || g_scan.at( g_th ).data == "bool"  ) {
      if ( g_ds == 0 )
        g_ds = 1 ; 
    } // if 
    else {
      if ( g_ds == 0 )
        g_ds = 2 ;
    } // else()
  } // if()
  else {
    g_th++ ; 
    if ( g_scan.at( g_th ).data == "void" || g_scan.at( g_th ).data == "int" || 
         g_scan.at( g_th ).data == "char" || g_scan.at( g_th ).data == "float" || 
         g_scan.at( g_th ).data == "string" || g_scan.at( g_th ).data == "bool"  ) {
      if ( g_ds == 0 )   
        g_ds = 1 ; 
    } // if 
    else {
      if ( g_ds == 0 )
        g_ds = 2 ;
    } // else()
  } // else()
  
  // if ( g_ds == 2 ) cout << "有對啦"; 
  
  if ( g_scan.at( g_th ).type == "not_defined" ) {
    g_ui = true ; 
    g_error_1 = true ; 
    g_error_2 = true ; 
    return ; 
  } // if 
  
  Save_token() ; 
  if ( S_defined() == false && g_ds == 2 ) return ;       
   
  while ( g_scan.at( g_th ).data == "\n" && g_th < g_scan.size()-1 ) {
    // cout << g_th << endl   ; 
    if ( g_scan.at( g_th ).data == "\n" && g_scan.at( g_th ).count != "used" ) // 數行數 
      g_line++ ; 
      
    g_scan.at( g_th ).count = "used" ; 
    g_th++;
    
    Save_token() ; 
    if ( S_defined() == false && g_ds == 2 ) return ;  
    
    if ( g_scan.at( g_th ).type == "not_defined" ) {
      g_error_1 = true ; 
      g_error_2 = true ; 
      return ; 
    } // if()
  } // while()
} // Get_next_token()


void If_next() { 
  if ( g_error_2 == false ) {
    
    g_og = g_th ; 
    if ( g_th < g_scan.size() - 2 ) // **有待研究 
      g_th++;
      
    if ( g_scan.at( g_th ).type == "not_defined" ) {  
      g_ui = true ; 
      g_error_1 = true ; 
      g_error_2 = true ; 
      return ; 
    } // if 
    
    Save_token() ; 
    if ( S_defined() == false && g_ds == 2 ) return ;  
    
    while ( g_scan.at( g_th ).data == "\n" ) {
      if ( g_scan.at( g_th ).data == "\n" && g_scan.at( g_th ).count != "used" ) // 數行數 
        g_line++ ; 
        
      Save_token() ; 
      if ( S_defined() == false && g_ds == 2 ) return ;  
       
      g_scan.at( g_th ).count = "used" ;   
      Get_next_token() ; 
    } // while()
  } // if()
} // If_next()

void Save_count( string s ) {
  if ( g_func_rest == 1 ) {  // 區域 
    // g_count_small.push_back( s ) ;
    
  }  // if()
} // Save_count() 

void User_input() { 
  if ( g_error_2 == true ) return ; 
  // cout << "User_input() : " << g_scan.at( g_th ).data << endl ; 
  // : ( definition | statement ) { definition | statement }
  
  if ( g_scan.at( g_th ).data == "void" || g_scan.at( g_th ).data == "int" || 
       g_scan.at( g_th ).data == "char" || g_scan.at( g_th ).data == "float" || 
       g_scan.at( g_th ).data == "string" || g_scan.at( g_th ).data == "bool"  ) {
    g_ds = 1 ; 
    Definition() ; 
  } // if 
  else {
     
    g_ds = 2 ; 
    Statement() ; 
  } // else()

} // User_input() 


void Definition() {  
  if ( g_error_2 == true ) return ; 
  // cout << "Definition() : " << g_scan.at( g_th ).data << endl ; 
   
  // :           VOID Identifier function_definition_without_ID 
  // | type_specifier Identifier function_definition_or_declarators
  if ( g_scan.at( g_th ).data == "void" ) {
    g_void = true ; 
    If_next() ; 
    if ( g_scan.at( g_th ).type == "IDENT" ) { 
      g_func_name = g_scan.at( g_th ).data ; // 本題function 名稱 
      If_next() ; 
      Function_definition_without_ID() ; 
    } // if()
    else {
      g_error_2 = true ; 
      return ; 
    } // else ()
  } // if()
  else if ( Type_specifier() == true ) {
    If_next() ; 
    if ( g_scan.at( g_th ).type == "IDENT" ) {
       
      
      If_next() ; 
      
      Function_definition_or_declarators() ;
    } // if()
    else {
      g_error_2 = true ; 
      return ; 
    } // else ()
  } // else if()
  else {
    g_error_2 = true ; 
    return ; 
  } // else()
  
} // Definition() 

bool Type_specifier() {  
  
  // cout << "Type_specifier() : " << g_scan.at( g_th ).data << endl ; 
  if ( g_scan.at( g_th ).data == "int" || g_scan.at( g_th ).data == "char" || 
       g_scan.at( g_th ).data == "float" || g_scan.at( g_th ).data == "string" || 
       g_scan.at( g_th ).data == "bool" ) {
    // g_ds = 1 ; 
    return true ; 
  } // if()
  else 
    return false ; 
} // Type_specifier() 

bool Type_specifier( string s ) {  
  
  // cout << "Type_specifier() : " << g_scan.at( g_th ).data << endl ; 
  if ( s == "int" || s == "char" || s == "float" || s == "string" || s == "bool" ) {
    // g_ds = 1 ; 
    return true ; 
  } // if()
  else 
    return false ; 
} // Type_specifier() 

void Function_definition_or_declarators() {  
  if ( g_error_2 == true ) return ; 
  // cout << "Function_definition_or_declarators() : " << g_scan.at( g_th ).data << endl ; 
   
  // : function_definition_without_ID
  // | rest_of_declarators
  if ( g_scan.at( g_th ).data == "(" ) {
    g_func_name = g_scan.at( g_og ).data ; // 存 function 名稱 
    if ( g_func_rest == 0 )
      g_func_rest = 1 ; // 是FUNTION 
    Function_definition_without_ID(); 
  } // if()
  else if ( g_scan.at( g_th ).data == "[" || g_scan.at( g_th ).data == "," || 
            g_scan.at( g_th ).data == ";" ) {
    if ( g_func_rest == 0 )
      g_func_rest = 2 ; // 是 REST 
    Rest_of_declarators() ; 
  } // else if()
  else {
    g_error_2 = true ; 
    return ; 
  } // else()

} // Function_definition_or_declarators() 

void Rest_of_declarators() {
  if ( g_error_2 == true ) return ;   
  // cout << "Rest_of_declarators() : " << g_scan.at( g_th ).data << endl ; 
  // : [ '[' Constant ']' ] 
  //  { ',' Identifier [ '[' Constant ']' ] } ';'
  g_count.push_back( g_scan.at( g_og ).data ) ; 
  if ( g_scan.at( g_th ).data == "[" ) { // ['['constant']']
    If_next() ; 
    if ( g_scan.at( g_th ).type == "constant" ) {
      g_array = g_scan.at( g_th ).data ; 
      If_next() ; 
      if ( g_scan.at( g_th ).data == "]" ) {
        If_next() ;  // 之後至少會接一個";" 
      } // if () 
      else { 
        g_error_2 = true ; 
        return ;        
      } // else()
    } // if()
    else {
      g_error_2 = true ; 
      return ; 
    } // else()
  } // if()
  
  Save_and_clear_temp() ; 
  if ( g_scan.at( g_th ).data == "," ) { 
    while ( g_scan.at( g_th ).data == "," ) {
      If_next() ; 
       
      if ( g_scan.at( g_th ).type == "IDENT" ) {
        g_data = g_scan.at( g_th ).data ; 
        g_count.push_back( g_scan.at( g_th ).data ) ; 
        g_count_small.push_back( g_scan.at( g_th ).data ) ;
        g_count_ready.at( g_c ).push_back( g_scan.at( g_th ).data ) ; 
        Save_count( g_scan.at( g_th ).data ) ; // 區域變數 
        
        If_next() ; 
        if ( g_scan.at( g_th ).data == "[" ) {
          If_next() ; 
          if ( g_scan.at( g_th ).type == "constant" ) {
            g_array = g_scan.at( g_th ).data ;
            If_next() ; 
            if ( g_scan.at( g_th ).data == "]" ) {
              If_next() ;  // 之後至少會接一個";" 
            } // if () 
            else { 
              g_error_2 = true ; 
              return ;        
            } // else()
          } // if()
          else {
            g_error_2 = true ; 
            return ; 
          } // else()
        } // if()    
         
        Save_and_clear_temp() ;   
      } // if()
      else {
        g_error_2 = true ; 
        return ; 
      } // else() 
    } // while()
    
    g_type = "" ; 
  } // if()
  
  if ( g_scan.at( g_th ).data != ";" ) {
    g_error_2 = true ; 
    return ; 
  } // if()
  

} // Rest_of_declarators() 

void Function_definition_without_ID() {  
  if ( g_error_2 == true ) return ; 
  // cout << "Function_definition_without_ID() : " << g_scan.at( g_th ).data << endl ; 
  // : '(' [ VOID | formal_parameter_list ] ')' compound_statement
  
  g_func_rest = 1 ; 
  if ( g_scan.at( g_th ).data == "(" ) { 
    If_next() ; 
  } // if()
  else {
    g_error_2 = true ; 
    return ; 
  } // else()
  
  if ( g_scan.at( g_th ).data == "void" ) {
    If_next() ; 
  } // if()
  else if ( Type_specifier() == true ) {
    Formal_parameter_list(); 
    If_next() ; 
  } // else if()

  if ( g_scan.at( g_th ).data == ")" ) { 
    If_next() ; 
  } // if()
  else {
    g_error_2 = true ; 
    return ; 
  } // else()

  if ( g_scan.at( g_th ).data == "{" ) { 
    Compound_statement() ; 
  } // if()
  else {
    g_error_2 = true ; 
    return ; 
  } // else ()

} // Function_definition_without_ID() 

void Formal_parameter_list() {  
  if ( g_error_2 == true ) return ; 
  // cout << "Formal_parameter_list() : " << g_scan.at( g_th ).data << endl ; 
  // : type_specifier [ '&' ] Identifier [ '[' Constant ']' ] 
  //  { ',' type_specifier [ '&' ] Identifier [ '[' Constant ']' ] }
  
  if ( Type_specifier() == true ) {
    If_next() ; 
  } // if()
  else {
    g_error_2 = true ; 
    return ; 
  } // else()
  
  if ( g_scan.at( g_th ).data == "&" ) // [ '&' ]
    If_next() ;
    
  if ( g_scan.at( g_th ).type == "IDENT" ) { // Identifier
    g_count_small.push_back( g_scan.at( g_th ).data );
    g_count_ready.at( 0 ).push_back( g_scan.at( g_th ).data ) ;
    If_next() ; 
  } // if()
  else {
    g_error_2 = true ; 
    return ; 
  } // else()    
  
  if ( g_scan.at( g_th ).data == "[" ) { // ['['constant']']
    If_next() ; 
    if ( g_scan.at( g_th ).type == "constant" ) {
      If_next() ; 
      if ( g_scan.at( g_th ).data == "]" ) {
        If_next() ;  // 之後至少會接一個";" 
      } // if () 
      else { 
        g_error_2 = true ; 
        return ;        
      } // else()
    } // if() 
    else {
      g_error_2 = true ; 
      return ; 
    } // else()
  } // if()
  
  

  while ( g_scan.at( g_th ).data == "," ) {
    If_next() ; 
    if ( Type_specifier() == true ) { // type_specifier
      If_next() ; 
    } // if()
    else {
      g_error_2 = true ; 
      return ; 
    } // else()
    
    if ( g_scan.at( g_th ).data == "&" ) // [ '&' ]
      If_next() ;
      
    if ( g_scan.at( g_th ).type == "IDENT" ) { // Identifier
      g_count_small.push_back( g_scan.at( g_th ).data );
      g_count_ready.at( 0 ).push_back( g_scan.at( g_th ).data ) ;
      If_next() ; 
    } // if()
    else {
      g_error_2 = true ; 
      return ; 
    } // else()    
    
    if ( g_scan.at( g_th ).data == "[" ) { // ['['constant']']
      If_next() ; 
      if ( g_scan.at( g_th ).type == "constant" ) {
        If_next() ; 
        if ( g_scan.at( g_th ).data == "]" ) {
          If_next() ;  // 之後至少會接一個";" 
        } // if () 
        else { 
          g_error_2 = true ; 
          return ;        
        } // else()
      } // if() 
      else {
        g_error_2 = true ; 
        return ; 
      } // else()
    } // if()    
  } // while()

  
  Go_back(); // 會多讀到一個 要還回來一次 
  // if ( g_error_2 == true  ) cout << "已經有錯" ;   
} // Formal_parameter_list() 

void Compound_statement() { 
  if ( g_error_2 == true ) return ; 
  // cout << "Compound_statement() : " << g_scan.at( g_th ).data << endl ; 
  // : '{' { declaration | statement } '}'

  if ( g_scan.at( g_th ).data == "{" ) {
    g_right_quote++; 
    g_count_ready.push_back( g_small ) ; 
    g_c++ ; 
    If_next() ;
  } // if()
  else {
    g_error_2 = true ; 
    return ; 
  } // else()
  
  if ( g_error_2 == true ) return ; 
  while ( g_scan.at( g_th ).data != "}" ) {
    if ( Type_specifier() == true )
      Declaration() ; 
    else 
      Statement() ; 
    if ( g_error_2 == true ) return ;  
    If_next() ;  
  } // while()
  /*
  for ( int i = 0 ; i < g_count_ready.size() ; i ++ ) 
    for ( int k = 0 ; k < g_count_ready.at(i).size() ; k++ ) 
      // if ( g_count_ready.at(i).at(k) != "fuck1999")
        cout << g_count_ready.at(i).at(k) << endl  ;
   cout << "***********" << endl ;
  */
  g_right_quote--;
  // if ( g_right_quote == 0 ) 
  //  Save_if();
  
  
  
  
  
  
  
  
  
  
  g_count_small.clear()  ;    
  g_c--; 
  g_count_ready.pop_back();

} // Compound_statement() 

void Declaration() { 
  
  if ( g_error_2 == true ) return ; 
  g_if = true ; 
  // g_ds = 1 ;
  // cout << "Declaration() : " << g_scan.at( g_th ).data << endl ; 
  // : type_specifier Identifier rest_of_declarators
  
  if ( Type_specifier() == true ) { // type_specifier
    g_type = g_scan.at( g_th ).data ; // if 
    If_next() ;  
  } // if()
  else {
    g_error_2 = true ; 
    return ; 
  } // else() 
  
  if ( g_scan.at( g_th ).type == "IDENT" ) { // Identifier
    g_data = g_scan.at( g_th ).data ;
    Save_count( g_scan.at( g_th ).data ) ; 
    g_count_small.push_back( g_scan.at( g_th ).data ) ;
    g_count_ready.at( g_c ).push_back( g_scan.at( g_th ).data ) ;
    If_next() ;
  } // if()
  else {
    g_error_2 = true ; 
    return ; 
  } // else() 
  
   
  if ( g_scan.at( g_th ).data == "[" || g_scan.at( g_th ).data == "," || 
       g_scan.at( g_th ).data == ";" ) {
    Rest_of_declarators();
  } // if()
  else {
    g_error_2 = true ; 
    return ; 
  } // else() 

} // Declaration() 

void Statement() { 
  if ( g_error_2 == true ) return ;  
  // cout << "Statement() : " << g_scan.at( g_th ).data << endl ; 
  
  // : ';'     // the null statement
  // | expression ';'  /* expression here should not be empty */
  // | RETURN [ expression ] ';'
  // | compound_statement
  // | IF '(' expression ')' statement [ ELSE statement ]
  // | WHILE '(' expression ')' statement
  // | DO statement WHILE '(' expression ')' ';'
  if ( g_scan.at( g_th ).data == "else" ) {
    g_error_2 = true ; 
    return ; 
  } // if()
  else if ( g_scan.at( g_th ).data == ";" ) {
    return ; 
  } // if()
  else if ( g_scan.at( g_th ).data == "return" ) {
    If_next() ;
    if ( g_scan.at( g_th ).data == ";" ) {
      return ; 
    } // if()
    else {
      Expression() ;
      if ( g_error_2 == true ) return ; 
      If_next() ;
    } // else()
    
    if ( g_scan.at( g_th ).data == ";" ) return ; 
    else {
      g_error_2 = true ; 
      return ;
    } // else
    
  } // else if()
  
  else if ( g_scan.at( g_th ).data == "{" ) {
    Compound_statement() ; 
    return ;
  } // else if()
  
  else if ( g_scan.at( g_th ).data == "if" ) {
    g_in_if = true ; 
    If_next() ;
    if ( g_scan.at( g_th ).data != "(" ) {
      g_error_2 = true ; 
      return ; 
    } // if()
    
    If_next() ;
    Expression();
    if ( g_error_2 == true ) return ;
    If_next() ;
    
    if ( g_scan.at( g_th ).data != ")" ) {
      g_error_2 = true ;
      return ; 
    } // if()
    
    If_next() ;
    Statement() ; 
    if ( g_error_2 == true ) return ;
    If_next() ;
    
    if ( g_scan.at( g_th ).data == "else" ) {
      // g_in_if = false ; 
      g_count_small.clear() ; 
      // g_count_ready.clear() ; 
      If_next() ;
      Statement() ;
      if ( g_error_2 == true ) return ;
    } // if()
    else {
      g_scan.at( g_th ).use = "" ;
      Go_back() ; 
      
      return ; 
    } // else
  } // else if()
  
  else if ( g_scan.at( g_th ).data == "while" ) {
    If_next() ;
    if ( g_scan.at( g_th ).data != "(" ) {
      g_error_2 = true ; 
      return ; 
    } // if()
    
    If_next() ;
    Expression();
    if ( g_error_2 == true ) return ;
    If_next() ;
    
    if ( g_scan.at( g_th ).data != ")" ) {
      g_error_2 = true ;
      return ; 
    } // if()
    
    If_next() ;
    Statement() ; 
    if ( g_error_2 == true ) return ;
    
  } // else if()
  
  else if ( g_scan.at( g_th ).data == "do" ) {
    If_next() ;
    Statement() ; 
    if ( g_error_2 == true ) return ;
    
    If_next() ;
    if ( g_scan.at( g_th ).data != "while" ) {
      g_error_2 = true ; 
      return ; 
    } // if()
    
    If_next() ;
    if ( g_scan.at( g_th ).data != "(" ) {
      g_error_2 = true ; 
      return ; 
    } // if()    
    
    If_next() ;
    Expression() ;
    if ( g_error_2 == true ) return ;
    
    If_next() ;
    if ( g_scan.at( g_th ).data != ")" ) {
      g_error_2 = true ; 
      return ; 
    } // if()     
    
    If_next() ;
    if ( g_scan.at( g_th ).data != ";" ) {
      g_error_2 = true ; 
      return ; 
    } // if()   
    
  } // else if()
  
  else { // Expression() ; 
    Expression() ; 
    if ( g_error_2 == true ) return ;
    If_next() ; 
    
    if ( g_scan.at( g_th ).data != ";" ) {
      g_error_2 = true ; 
      return ; 
    } // if 
  } // else()
  
} // Statement() 
    
void Expression() { 
  if ( g_error_2 == true ) return ; 
  // cout << "Expression() : " << g_scan.at( g_th ).data << endl ; 
  // : basic_expression { ',' basic_expression }
  
  Basic_expression();
  if ( g_error_2 == true ) return ;
  
  If_next() ; 
  while ( g_scan.at( g_th ).data == "," ) {
    If_next() ;
    Basic_expression() ;
    if ( g_error_2 == true ) return ;
    If_next() ;
  } // while()
  
  Go_back(); 

} // Expression() 

bool Check_func() {
  bool check = false ; 
  // cout << "***" << g_scan.at( g_th ).data << endl ; 
  
  for ( int i = 0 ; i < g_aldef.size() ; i++ ) {  // 檢查是否曾經存過 函數名稱 EX:cin . cout  
    if ( g_scan.at( g_th ).data == g_aldef.at( i ) ) 
      check = true ;  
      // cout << "++" << endl; 
  } // for()
  
  for ( int i = 0 ; i < g_func_list.size() ; i++ ) {  // 檢查是否曾經存過 函數名字  
    if ( g_scan.at( g_th ).data == g_func_list.at( i ).at( 1 ) ) 
      check = true ;  
      // cout << "++" << endl; 
  } // for()
  
  for ( int i = 0 ; i < g_count_small.size() ; i++ ) {  // 檢查是否曾經存過  區域變數 
    if ( g_scan.at( g_th ).data == g_count_small.at( i ) ) 
      check = true ;  
      // cout << "++" << endl; 
  } // for()
  
  for ( int k = 0 ; k < g_count_ready.size() ; k++ ) {
    for ( int i = 0 ; i < g_count_ready.at( k ).size() ; i++ ) {  // 檢查是否曾經存過  大區域變數 
      if ( g_scan.at( g_th ).data == g_count_ready.at( k ).at( i ) ) 
        check = true ;  
      // cout << "++" << endl; 
    } // for()
  } // for()
  
  
  
  for ( int i = 0 ; i < g_name_list.size() ; i++ ) {  // 檢查是否曾經存過  全域變數 
    if ( g_scan.at( g_th ).data == g_name_list.at( i ).at( 1 ) ) 
      check = true ;  
      // cout << "--" << endl ; 
  } // for()
  
  for ( int i = 0 ; i < g_func_list.size() ; i++ ) {  // 檢查是否曾經存過  全域變數 
    if ( g_scan.at( g_th ).data == g_func_list.at( i ).at( 1 ) ) 
      check = true ;  
      // cout << "--" << endl ; 
  } // for()
  
  if ( check == false ) { // 若從未存過 
    g_error_2 = true ; 
    g_error_3 = true ;
    // cout << "沒有存過" << g_scan.at( g_th ).data << endl ; 
    return false ; 
  } // if()
  else {
    return true ; 
  } // else()
      
  
  return true ; 
  
} // Check_func()

void Basic_expression() {
  if ( g_error_2 == true ) return ;  
  // cout << "Basic_expression() : " << g_scan.at( g_th ).data << endl ; 
  
  // : Identifier rest_of_Identifier_started_basic_exp
  // | ( PP | MM ) Identifier rest_of_PPMM_Identifier_started_basic_exp
  // | sign { sign } signed_unary_exp romce_and_romloe
  // | ( Constant | '(' expression ')' ) romce_and_romloe
  
  if ( g_scan.at( g_th ).type == "IDENT" ) {
    Check_func() ;
    If_next() ;
    if ( g_error_2 == true ) return ;
    Rest_of_Identifier_started_basic_exp() ; 
  } // if()
   
  
  else if ( g_scan.at( g_th ).data == "++" ||  g_scan.at( g_th ).data == "--" ) {
    If_next() ;
    if ( g_scan.at( g_th ).type == "IDENT" ) {
      Check_func() ;
      If_next() ;
    } // if()
    else {
      g_error_2 = true; 
      return ; 
    } // else 
    
    Rest_of_PPMM_Identifier_started_basic_exp() ; 
  } // else if()
  
  else if ( Sign() == true ) {
    while ( Sign() == true ) {
      If_next() ;
    } // while()
    
    Signed_unary_exp() ;
    if ( g_error_2 == true ) return ; 
    If_next() ;  
    Romce_and_romloe() ; 
  } // else if()
  
  else if ( g_scan.at( g_th ).type == "constant" || 
            g_scan.at( g_th ).data == "(" ) {
    if ( g_scan.at( g_th ).type == "constant" ) { 
      If_next() ;  
    } // if()
    else if ( g_scan.at( g_th ).data == "(" ) {
      If_next() ; 
      Expression() ; 
      if ( g_error_2 == true ) return ;
      If_next() ;
      if ( g_scan.at( g_th ).data == ")" ) {
        If_next() ;
      } // if()
      else {
        g_error_2 = true ; 
        return ;         
      } // else ()
    } // else if()

    Romce_and_romloe() ; 
  } // else if()
  
  else {
    g_error_2 = true ; 
    return ; 
  } // else()
  
} // Basic_expression() 

void Rest_of_Identifier_started_basic_exp() { 
  if ( g_error_2 == true ) return ; 
  // cout << "Rest_of_Identifier_started_basic_exp() : " << g_scan.at( g_th ).data << endl ; 
  // : [ '[' expression ']' ]
  //   ( assignment_operator basic_expression 
  //     | 
  //     [ PP | MM ] romce_and_romloe 
  //   )
  // | '(' [ actual_parameter_list ] ')' romce_and_romloe
  
  if ( g_scan.at( g_th ).data == "(" ) {
    If_next() ;
    if ( g_scan.at( g_th ).data == ")" ) {
      If_next() ;
    } // if()
    else {
      Actual_parameter_list();
      if ( g_error_2 == true ) return ;
      If_next() ;
      if ( g_scan.at( g_th ).data == ")" ) {
        If_next() ;
      } // if
      else {
        g_error_2 = true ; 
        return ;         
      } // else()
    } // else() 
    
    Romce_and_romloe() ; 
  } // if()
  else {
    if ( g_scan.at( g_th ).data == "[" ) { // [ '[' expression ']' ]
      If_next() ;
      Expression() ; 
      if ( g_error_2 == true ) return ;
      If_next() ;
      if ( g_scan.at( g_th ).data == "]" ) {
        If_next() ;
      } // if()
      else {
        g_error_2 = true ; 
        return ; 
      } // else
    } // if()
    
    if ( Assignment_operator() == true ) {
      If_next() ;
      Basic_expression() ; 
    } // if()
    else {
      if ( g_scan.at( g_th ).data == "++" ||  g_scan.at( g_th ).data == "--" ) {
        If_next() ;
      } // if()
      
      Romce_and_romloe() ; 
    } // else()
  } // else()
} // Rest_of_Identifier_started_basic_exp()

void Rest_of_PPMM_Identifier_started_basic_exp() { 
  if ( g_error_2 == true ) return ; 
  // cout << "Rest_of_PPMM_Identifier_started_basic_exp() : " << g_scan.at( g_th ).data << endl ; 
  
  // : [ '[' expression ']' ] romce_and_romloe 
  if ( g_scan.at( g_th ).data == "[" ) { // 0~1 
    If_next() ;
    Expression() ; 
    if ( g_error_2 == true ) return ; 
    If_next() ;
    if ( g_scan.at( g_th ).data == "]" ) 
      If_next() ;
    else {
      g_error_2 = true ; 
      return ; 
    } // else()
  } // if()
  
  if ( g_error_2 == true ) return ; 
  Romce_and_romloe() ; 
  
} // Rest_of_PPMM_Identifier_started_basic_exp()  

bool Sign() { 
  // cout << "Sign() : " << g_scan.at( g_th ).data << endl ; 
  // : '+' | '-' | '!'
  if ( g_scan.at( g_th ).data == "+" || g_scan.at( g_th ).data == "-" || 
       g_scan.at( g_th ).data == "!" )
    return true ; 
  else 
    return false ; 
} // Sign() 

void Actual_parameter_list() {  
  if ( g_error_2 == true ) return ; 
  // cout << "Actual_parameter_list() : " << g_scan.at( g_th ).data << endl ; 
  // : basic_expression { ',' basic_expression }
  
  Basic_expression() ; 
  if ( g_error_2 == true ) return ;  
  If_next() ;
  if ( g_scan.at( g_th ).data == "," ) {
    while ( g_scan.at( g_th ).data == "," ) {
      If_next() ;
      Basic_expression() ;
      if ( g_error_2 == true ) return ; 
      If_next() ;
    } // while  
  } // if 
  
  Go_back(); 
  
 
} // Actual_parameter_list() 

bool Assignment_operator() { 
    
  // cout << "Assignment_operatort() : " << g_scan.at( g_th ).data << endl ; 
  // : '=' | TE | DE | RE | PE | ME
  if ( g_scan.at( g_th ).data == "+=" || g_scan.at( g_th ).data == "-=" || g_scan.at( g_th ).data == "*=" ||
       g_scan.at( g_th ).data == "/=" || g_scan.at( g_th ).data == "%=" || g_scan.at( g_th ).data == "=" )
    return true ; 
  else 
    return false ;
} // Assignment_operator() 

void Romce_and_romloe() {  // 即romce_and_romloe
  if ( g_error_2 == true ) return ; 
  // cout << "Romce_and_romloe() : " << g_scan.at( g_th ).data << endl ; 
  // : rest_of_maybe_logical_OR_exp [ '?' basic_expression ':' basic_expression ]
  Rest_of_maybe_logical_OR_exp() ; 
  if ( g_error_2 == true ) return ; 
  If_next() ;
  if ( g_scan.at( g_th ).data == "?" ) {
    If_next() ;
    Basic_expression() ; 
    if ( g_error_2 == true ) return ; 
    If_next() ;
    if ( g_scan.at( g_th ).data == ":" ) {
      If_next() ;
      Basic_expression() ; 
      if ( g_error_2 == true ) return ; 
    } // if()
    else {
      g_error_2 = true ; 
    } // else()
  } // if()
  else {
    Go_back(); 
  } // else()
  
} // Romce_and_romloe() 

void Rest_of_maybe_logical_OR_exp() {  
  if ( g_error_2 == true ) return ; 
  // cout << "Rest_of_maybe_logical_OR_exp() : " << g_scan.at( g_th ).data << endl ; 
  // : rest_of_maybe_logical_AND_exp { OR maybe_logical_AND_exp }
  Rest_of_maybe_logical_AND_exp() ; 
  if ( g_error_2 == true ) return ; 
  If_next() ;
  if ( g_scan.at( g_th ).data == "||" ) {
    while ( g_scan.at( g_th ).data == "||" ) {
      If_next() ;
      Maybe_logical_AND_exp() ; 
      if ( g_error_2 == true ) return ; 
      If_next() ;
    } // while()
  } // if()
  
  Go_back();  
} // Rest_of_maybe_logical_OR_exp() 

void Maybe_logical_AND_exp() {  
  if ( g_error_2 == true ) return ;  
  // cout << "Maybe_logical_AND_exp() : " << g_scan.at( g_th ).data << endl ; 
  // : maybe_bit_OR_exp { AND maybe_bit_OR_exp }
  Maybe_bit_OR_exp() ; 
  if ( g_error_2 == true ) return ; 
  If_next() ;
  if ( g_scan.at( g_th ).data == "&&" ) {
    while ( g_scan.at( g_th ).data == "&&" ) {
      If_next() ;
      Maybe_bit_OR_exp() ;
      if ( g_error_2 == true ) return ; 
      If_next() ;
    } // while()
  } // if()
  
  Go_back();
  
} // Maybe_logical_AND_exp() 

void Rest_of_maybe_logical_AND_exp() {
  if ( g_error_2 == true ) return ; 
  // cout << "Rest_of_maybe_logical_AND_exp() : " << g_scan.at( g_th ).data << endl ; 
  // : rest_of_maybe_bit_OR_exp { AND maybe_bit_OR_exp }
  Rest_of_maybe_bit_OR_exp() ;
  if ( g_error_2 == true ) return ;  
  If_next() ;
  if ( g_scan.at( g_th ).data == "&&" ) {
    while ( g_scan.at( g_th ).data == "&&" ) {
      If_next() ;
      Maybe_bit_OR_exp() ;
      if ( g_error_2 == true ) return ; 
      If_next() ;
    } // while()
  } // if()
  
  Go_back();
} // Rest_of_maybe_logical_AND_exp() 


void Maybe_bit_OR_exp() {  
  if ( g_error_2 == true ) return ; 
  // cout << "Maybe_bit_OR_exp() : " << g_scan.at( g_th ).data << endl ; 
  // : maybe_bit_ex_OR_exp { '|' maybe_bit_ex_OR_exp }

  Maybe_bit_ex_OR_exp() ; 
  if ( g_error_2 == true ) return ; 
  If_next() ;
  if ( g_scan.at( g_th ).data == "|" ) {
    while ( g_scan.at( g_th ).data == "|" ) {
      If_next() ;
      Maybe_bit_ex_OR_exp() ;
      if ( g_error_2 == true ) return ; 
      If_next() ;
    } // while()
  } // if()
  
  Go_back();
    
} // Maybe_bit_OR_exp() 

void Rest_of_maybe_bit_OR_exp() {
  if ( g_error_2 == true ) return ;  
  // cout << "Rest_of_maybe_bit_OR_exp() : " << g_scan.at( g_th ).data << endl ; 
  // : rest_of_maybe_bit_ex_OR_exp { '|' maybe_bit_ex_OR_exp }
  Rest_of_maybe_bit_ex_OR_exp() ; 
  if ( g_error_2 == true ) return ; 
  If_next() ;
  if ( g_scan.at( g_th ).data == "|" ) {
    while ( g_scan.at( g_th ).data == "|" ) {
      If_next() ;
      Maybe_bit_ex_OR_exp() ;
      if ( g_error_2 == true ) return ; 
      If_next() ;
    } // while()
  } // if()
  
  Go_back();
} // Rest_of_maybe_bit_OR_exp() 

void Maybe_bit_ex_OR_exp() {  
  if ( g_error_2 == true ) return ; 
  // cout << "Maybe_bit_ex_OR_exp() : " << g_scan.at( g_th ).data << endl ; 
  // : maybe_bit_AND_exp { '^' maybe_bit_AND_exp }
  Maybe_bit_AND_exp() ; 
  if ( g_error_2 == true ) return ; 
  If_next() ;
  if ( g_scan.at( g_th ).data == "^" ) {
    while ( g_scan.at( g_th ).data == "^" ) {
      If_next() ;
      Maybe_bit_AND_exp() ;
      if ( g_error_2 == true ) return ; 
      If_next() ;
    } // while()
  } // if()
  
  Go_back();
} // Maybe_bit_ex_OR_exp() 

void Rest_of_maybe_bit_ex_OR_exp() {
  if ( g_error_2 == true ) return ;  
  // cout << "Rest_of_maybe_bit_ex_OR_exp() : " << g_scan.at( g_th ).data << endl ; 
  // : rest_of_maybe_bit_AND_exp { '^' maybe_bit_AND_exp }
  Rest_of_maybe_bit_AND_exp() ; 
  if ( g_error_2 == true ) return ; 
  If_next() ;
  if ( g_scan.at( g_th ).data == "^" ) {
    while ( g_scan.at( g_th ).data == "^" ) {
      If_next() ;
      Maybe_bit_AND_exp() ;
      if ( g_error_2 == true ) return ; 
      If_next() ;
    } // while()
  } // if()
  
  Go_back();
  
} // Rest_of_maybe_bit_ex_OR_exp() 

void Maybe_bit_AND_exp() {  
  if ( g_error_2 == true ) return ;  
  // cout << "Maybe_bit_AND_exp() : " << g_scan.at( g_th ).data << endl ; 
  // : maybe_equality_exp { '&' maybe_equality_exp }
  Maybe_equality_exp() ; 
  if ( g_error_2 == true ) return ; 
  If_next() ;
  if ( g_scan.at( g_th ).data == "&" ) {
    while ( g_scan.at( g_th ).data == "&" ) {
      If_next() ;
      Maybe_equality_exp() ;
      if ( g_error_2 == true ) return ; 
      If_next() ;
    } // while()
  } // if()
  
  Go_back();
  
} // Maybe_bit_AND_exp() 

void Rest_of_maybe_bit_AND_exp() { 
  if ( g_error_2 == true ) return ;  
  // cout << "Rest_of_maybe_bit_AND_exp() : " << g_scan.at( g_th ).data << endl ; 
  // : rest_of_maybe_equality_exp { '&' maybe_equality_exp }
  Rest_of_maybe_equality_exp() ; 
  if ( g_error_2 == true ) return ; 
  If_next() ;
  if ( g_scan.at( g_th ).data == "&" ) {
    while ( g_scan.at( g_th ).data == "&" ) {
      If_next() ;
      Maybe_equality_exp() ;
      if ( g_error_2 == true ) return ; 
      If_next() ;
    } // while()
  } // if()
  
  Go_back();
} // Rest_of_maybe_bit_AND_exp() 

void Maybe_equality_exp() {  
  if ( g_error_2 == true ) return ;  
  // cout << "Maybe_equality_exp() : " << g_scan.at( g_th ).data << endl ; 
  // : maybe_relational_exp 
  //  { ( EQ | NEQ ) maybe_relational_exp}
  Maybe_relational_exp() ; 
  if ( g_error_2 == true ) return ; 
  If_next() ;
  if ( g_scan.at( g_th ).data == "==" || g_scan.at( g_th ).data == "!=" ) {
    while ( g_scan.at( g_th ).data == "==" || g_scan.at( g_th ).data == "!=" ) {
      If_next() ;
      Maybe_relational_exp() ;
      if ( g_error_2 == true ) return ; 
      If_next() ;
    } // while()
  } // if()
  
  Go_back();
} // Maybe_equality_exp() 

void Rest_of_maybe_equality_exp() { 
  if ( g_error_2 == true ) return ;  
  // cout << "Rest_of_maybe_equality_exp() : " << g_scan.at( g_th ).data << endl ; 
  // : rest_of_maybe_relational_exp 
  //  { ( EQ | NEQ ) maybe_relational_exp }
  Rest_of_maybe_relational_exp() ;
  if ( g_error_2 == true ) return ;  
  If_next() ;
  if ( g_scan.at( g_th ).data == "==" || g_scan.at( g_th ).data == "!=" ) {
    while ( g_scan.at( g_th ).data == "==" || g_scan.at( g_th ).data == "!=" ) {
      If_next() ;
      Maybe_relational_exp() ;
      if ( g_error_2 == true ) return ; 
      If_next() ;
    } // while()
  } // if()
  
  Go_back();
} // Rest_of_maybe_equality_exp() 

void Maybe_relational_exp() {  
  if ( g_error_2 == true ) return ;  
  // cout << "Maybe_relational_exp() : " << g_scan.at( g_th ).data << endl ; 
  // : maybe_shift_exp 
  //  { ( '<' | '>' | LE | GE ) maybe_shift_exp }
  Maybe_shift_exp() ; 
  if ( g_error_2 == true ) return ; 
  If_next() ;
  if ( g_scan.at( g_th ).data == ">=" || g_scan.at( g_th ).data == "<=" || 
       g_scan.at( g_th ).data == ">" || g_scan.at( g_th ).data == "<" ) {
    while ( g_scan.at( g_th ).data == ">=" || g_scan.at( g_th ).data == "<=" || 
            g_scan.at( g_th ).data == ">" || g_scan.at( g_th ).data == "<" ) {
      If_next() ;
      Maybe_shift_exp() ;
      if ( g_error_2 == true ) return ; 
      If_next() ;
    } // while()
  } // if()
  
  Go_back();
} // Maybe_relational_exp() 

void Rest_of_maybe_relational_exp() { 
  if ( g_error_2 == true ) return ;  
  // cout << "Rest_of_maybe_relational_exp() : " << g_scan.at( g_th ).data << endl ;  
  // : rest_of_maybe_shift_exp 
  //  { ( '<' | '>' | LE | GE ) maybe_shift_exp }
  Rest_of_maybe_shift_exp() ; 
  if ( g_error_2 == true ) return ; 
  If_next() ;
  if ( g_scan.at( g_th ).data == ">=" || g_scan.at( g_th ).data == "<=" || 
       g_scan.at( g_th ).data == ">" || g_scan.at( g_th ).data == "<" ) {
    while ( g_scan.at( g_th ).data == ">=" || g_scan.at( g_th ).data == "<=" || 
            g_scan.at( g_th ).data == ">" || g_scan.at( g_th ).data == "<" ) {
      If_next() ;
      Maybe_shift_exp() ;
      if ( g_error_2 == true ) return ; 
      If_next() ;
    } // while()
  } // if()
  
  Go_back();
} // Rest_of_maybe_relational_exp() 

void Maybe_shift_exp() {  
  if ( g_error_2 == true ) return ;  
  // cout << "Maybe_shift_exp() : " << g_scan.at( g_th ).data << endl ; 
  // : maybe_additive_exp { ( LS | RS ) maybe_additive_exp }
  Maybe_additive_exp() ; 
  if ( g_error_2 == true ) return ; 
  If_next() ;
  if ( g_scan.at( g_th ).data == "<<" || g_scan.at( g_th ).data == ">>" ) {
    while ( g_scan.at( g_th ).data == "<<" || g_scan.at( g_th ).data == ">>" ) {
      If_next() ;
      Maybe_additive_exp() ;
      if ( g_error_2 == true ) return ; 
      If_next() ;
    } // while()
  } // if()
  
  Go_back();
    
} // Maybe_shift_exp() 

void Rest_of_maybe_shift_exp() { 
  if ( g_error_2 == true ) return ;  
  // cout << "Rest_of_maybe_shift_exp() : " << g_scan.at( g_th ).data << endl ; 
  // : rest_of_maybe_additive_exp { ( LS | RS ) maybe_additive_exp }
  Rest_of_maybe_additive_exp() ;
  if ( g_error_2 == true ) return ;  
  If_next() ;
  if ( g_scan.at( g_th ).data == "<<" || g_scan.at( g_th ).data == ">>" ) {
    while ( g_scan.at( g_th ).data == "<<" || g_scan.at( g_th ).data == ">>" ) {
      If_next() ;
      Maybe_additive_exp() ;
      if ( g_error_2 == true ) return ; 
      If_next() ;
    } // while()
  } // if()
  
  Go_back();
} // Rest_of_maybe_shift_exp() 


void Maybe_additive_exp() { 
  if ( g_error_2 == true ) return ;  
  // cout << "Maybe_additive_exp() : " << g_scan.at( g_th ).data << endl ;  
  // : maybe_mult_exp { ( '+' | '-' ) maybe_mult_exp }
  
  Maybe_mult_exp() ;
  if ( g_error_2 == true ) return ;  
  If_next() ;
  if ( g_scan.at( g_th ).data == "+" || g_scan.at( g_th ).data == "-" ) {
    while ( g_scan.at( g_th ).data == "+" || g_scan.at( g_th ).data == "-" ) {
      If_next() ;
      Maybe_mult_exp() ;
      if ( g_error_2 == true ) return ; 
      If_next() ;
    } // while()
  } // if()
  
  Go_back();
  
} // Maybe_additive_exp() 

void Rest_of_maybe_additive_exp() { 
  if ( g_error_2 == true ) return ;   
  // cout << "Rest_of_maybe_additive_exp() : " << g_scan.at( g_th ).data << endl ; 
  // : rest_of_maybe_mult_exp { ( '+' | '-' ) maybe_mult_exp }
  
  
  if ( g_scan.at( g_th ).data == "*" || g_scan.at( g_th ).data == "/" || 
       g_scan.at( g_th ).data == "%" ) {
    Rest_of_maybe_mult_exp() ;
    if ( g_error_2 == true ) return ;  
    If_next() ;
  } // if()
  
  if ( g_scan.at( g_th ).data == "+" || g_scan.at( g_th ).data == "-" ) {
    while ( g_scan.at( g_th ).data == "+" || g_scan.at( g_th ).data == "-" ) {
      If_next() ;
      Maybe_mult_exp() ;
      if ( g_error_2 == true ) return ; 
      If_next() ;
    } // while()
  } // if()
  
  Go_back();

} // Rest_of_maybe_additive_exp() 


void Maybe_mult_exp() {  
  if ( g_error_2 == true ) return ;  
  // cout << "Maybe_mult_exp() : " << g_scan.at( g_th ).data << endl ; 
  // : unary_exp rest_of_maybe_mult_exp
  Unary_exp() ; 
  if ( g_error_2 == true ) return ; 
  
  If_next() ;
  if ( g_scan.at( g_th ).data == "*" || g_scan.at( g_th ).data == "/" || 
       g_scan.at( g_th ).data == "%" ) {
    Rest_of_maybe_mult_exp() ;
    if ( g_error_2 == true ) return ;  
  } // if()
  else {
    Go_back(); 
  } // else()

} // Maybe_mult_exp() 

void Rest_of_maybe_mult_exp() { 
  if ( g_error_2 == true ) return ; 
  // cout << "Rest_of_maybe_mult_exp() : " << g_scan.at( g_th ).data << endl ;  
  // : { ( '*' | '/' | '%' ) unary_exp }  /* could be empty ! */
  
  if ( g_scan.at( g_th ).data == "*" || g_scan.at( g_th ).data == "/" || 
       g_scan.at( g_th ).data == "%" ) {
    while ( g_scan.at( g_th ).data == "*" || g_scan.at( g_th ).data == "/" || 
            g_scan.at( g_th ).data == "%"  ) {
      If_next() ;
      Unary_exp() ;
      if ( g_error_2 == true ) return ;
      If_next() ;
    } // while()
    
    Go_back(); 
  } // if()


} // Rest_of_maybe_mult_exp() 


void Unary_exp() { 
  if ( g_error_2 == true ) return ;  
  // cout << "Unary_exp() : " << g_scan.at( g_th ).data << endl ;  
  // : sign { sign } signed_unary_exp
  // | unsigned_unary_exp
  // | ( PP | MM ) Identifier [ '[' expression ']' ]
  
  if ( Sign() == true ) {
    while ( Sign() == true ) {
      If_next() ;
    } // while()
    
    if ( g_scan.at( g_th ).type == "IDENT" || g_scan.at( g_th ).type == "constant" || 
         g_scan.at( g_th ).data == "(" ) {
      Signed_unary_exp();
      if ( g_error_2 == true ) return ;
    } // if()
    else {
      g_error_2 = true ; 
      return ; 
    } // else()
  } // if()
  else if ( g_scan.at( g_th ).type == "IDENT" || g_scan.at( g_th ).type == "constant" || 
            g_scan.at( g_th ).data == "(" ) {
    Unsigned_unary_exp() ; 
    if ( g_error_2 == true ) return ;
  } // else if()
  else if ( g_scan.at( g_th ).data == "++" || g_scan.at( g_th ).data == "--" ) {
    If_next() ;
    if ( g_scan.at( g_th ).type == "IDENT" ) {
      If_next() ;
    } // if(0
    else {
      g_error_2 = true ; 
      return ; 
    } // else  
    
    
    if ( g_scan.at( g_th ).data == "[" ) {
      If_next() ;
      Expression();
      if ( g_error_2 == true ) return ;
      If_next() ;
      if ( g_scan.at( g_th ).data != "]" ) {
        g_error_2 = true ; 
        return ; 
      } // if
    } // if()
    else {
      Go_back();  // 如果不是"[" 就補回來 
    } // else()    
  } // else if() 
  else {
    g_error_2 = true ; 
    return ; 
  } // else 
 
} // Unary_exp() 


void Signed_unary_exp() { 
  if ( g_error_2 == true ) return ;  
  // cout << "Signed_unary_exp() : " << g_scan.at( g_th ).data << endl ; 
  // : Identifier [ '(' [ actual_parameter_list ] ')' 
  //                |
  //                '[' expression ']'
  //              ]
  // | Constant 
  // | '(' expression ')'
  
  if ( g_scan.at( g_th ).type == "IDENT" ) { // Identifier
    Check_func() ; 
    If_next() ;
    
    if ( g_scan.at( g_th ).data == "(" ) {
      If_next() ;
      if ( g_scan.at( g_th ).data == ")" ) {
        return ; 
      } // if 
      else {
        Actual_parameter_list() ; 
        if ( g_error_2 == true ) return ;
        If_next() ;
        if ( g_scan.at( g_th ).data != ")" ) {
          g_error_2 = true ; 
          return ; 
        } // if()
      } // else()
    } // if()
    else if ( g_scan.at( g_th ).data == "[" ) {
      If_next() ;
      if ( g_scan.at( g_th ).data == "]" ) {
        g_error_2 = true ; 
        return ; 
      } // if 
      else {
        Expression() ;
        if ( g_error_2 == true ) return ; 
        If_next() ;
        if ( g_scan.at( g_th ).data != "]" ) {
          g_error_2 = true ; 
          return ; 
        } // if()
      } // else()      
    } // else if ()
    else {
      Go_back(); 
    } // else()
  } // if()
  else if ( g_scan.at( g_th ).type == "constant" ) { // constant
    return ; 
  } // else if()
  else if ( g_scan.at( g_th ).data == "(" ) { // '(' expression ')'
    If_next() ;
    Expression() ; 
    if ( g_error_2 == true ) return ;
    If_next() ;
    if ( g_scan.at( g_th ).data != ")" ) {
      g_error_2 = true ; 
      return ; 
    } // if()
  } // else if()
  else {
    g_error_2 = true ; 
    return ; 
  } // else 
  

} // Signed_unary_exp() 


void Unsigned_unary_exp() {
  if ( g_error_2 == true ) return ;  
  // cout << "Unsigned_unary_exp() : " << g_scan.at( g_th ).data << endl ;  
  // : Identifier [ '(' [ actual_parameter_list ] ')' 
  //                |
  //                [ '[' expression ']' ] [ ( PP | MM ) ]
  //              ]
  // | Constant 
  // | '(' expression ')'
  
  if ( g_scan.at( g_th ).type == "IDENT" ) {     // Identifier 
    Check_func() ; 
    If_next() ;
    
    if ( g_scan.at( g_th ).data == "(" ) {
      If_next() ;
      if ( g_scan.at( g_th ).data == ")" ) {
        return ; 
      } // if 
      else {
        Actual_parameter_list() ; 
        if ( g_error_2 == true ) return ;
        If_next() ;
        if ( g_scan.at( g_th ).data != ")" ) {
          g_error_2 = true ; 
          return ; 
        } // if()
      } // else()
    } // if()
    else if ( g_scan.at( g_th ).data == "[" || g_scan.at( g_th ).data == "++" || 
              g_scan.at( g_th ).data == "--"  ) {
      if ( g_scan.at( g_th ).data == "[" ) {
        If_next() ;
        Expression(); 
        if ( g_error_2 == true ) return ;
        If_next() ;
        
        if ( g_scan.at( g_th ).data == "]" ) {
          If_next() ;
          if ( g_scan.at( g_th ).data != "++" && g_scan.at( g_th ).data != "--" )
            Go_back();
        } // if()
        else {
          g_error_2 = true ; 
          return ; 
        } // else()
      } // if()
    } // else if()
    else 
      Go_back();
  } // if()
  else if ( g_scan.at( g_th ).type == "constant" ) {  // constant 
    return ; 
  } // else if()
  else if ( g_scan.at( g_th ).data == "(" ) {    // '(' expression ')' 
    If_next() ;
    Expression() ; 
    if ( g_error_2 == true ) return ;
    If_next() ;
    if ( g_scan.at( g_th ).data != ")" ) {
      g_error_2 = true ; 
      return ; 
    } // if()
  } // else if()
  else {
    g_error_2 = true ; 
    return ; 
  } // else 

} // Unsigned_unary_exp() 



void Scanner() { 
  //
  User_input() ; 
} // Scanner()

void Get_next_line_token() {
  while ( g_scan.at( g_th ).data != "\n" && g_th < g_scan.size()-1 ) { 
    g_th++;
  } // while()
} // Get_next_line_token()

bool Check_defined( string s ) {
  bool check = false ; 
  
  if ( g_func_rest == 1 ) {   // function 檢查 
    // cout << "有近來" << endl ; 
    for ( int i = 0 ; i < g_func_list.size() ; i++ ) {
      if ( s == g_func_list.at( i ).at( 1 ) ) return true ; 
    } // for()
  } // if()
  
  if ( g_func_rest == 2 ) {    // variable檢查 
    for ( int i = 0  ; i < g_name_list.size() ; i++ ) {
      if ( s == g_name_list.at( i ).at( 1 ) ) return true ; 
    } // for()
  } // if
  
  return false ; 
  
} // Check_defined()

void Push_in() {
  g_aldef.push_back( "return" ) ;
  g_aldef.push_back( "while" ) ;
  g_aldef.push_back( "if" ) ;
  g_aldef.push_back( "else" ) ;
  g_aldef.push_back( "do" ) ;
  g_aldef.push_back( "cout" ) ;
  g_aldef.push_back( "cin" ) ;
  g_aldef.push_back( "Done" ) ;
  g_aldef.push_back( "ListAllVariables" ) ;
  g_aldef.push_back( "ListAllFunctions" ) ;
  g_aldef.push_back( "ListVariable" ) ;
  g_aldef.push_back( "ListFunction" ) ;
  
} // Push_in()

void ListAllVariables() {
  g_temp = g_name_list ;
  string temp = ""; 
  int count = 0 ;
  
  for ( int i = g_temp.size()-1 ; i > 0 ; i-- ) {
    for ( int j = 0 ; j <= i-1 ; j++ ) {
      if ( g_temp.at( j ).at( 1 ) > g_temp.at( j+1 ).at( 1 ) ) {
        temp = g_temp.at( j ).at( 1 );
        g_temp.at( j ).at( 1 ) = g_temp.at( j+1 ).at( 1 );
        g_temp.at( j+1 ).at( 1 ) = temp;
      } // if()
    } // for()
  } // for()
  
  cout << "> " ;
  for ( int i = 0 ; i < g_temp.size() ; i++ ) 
    cout << g_temp.at( i ).at( 1 ) << endl ; 
  cout << "Statement executed ..." << endl ;
  
} // ListAllVariables()

void ListAllFunctions() {
  g_temp = g_func_list ;
  string temp = ""; 
  int count = 0 ;
  
  for ( int i = g_temp.size()-1 ; i > 0 ; i-- ) {
    for ( int j = 0 ; j <= i-1 ; j++ ) {
      if ( g_temp.at( j ).at( 1 ) > g_temp.at( j+1 ).at( 1 ) ) {
        temp = g_temp.at( j ).at( 1 );
        g_temp.at( j ).at( 1 ) = g_temp.at( j+1 ).at( 1 );
        g_temp.at( j+1 ).at( 1 ) = temp;
      } // if()
    } // for()
  } // for()
  
  cout << "> " ;
  for ( int i = 0 ; i < g_temp.size() ; i++ ) 
    cout << g_temp.at( i ).at( 1 ) << "()" << endl ; 
  cout << "Statement executed ..." << endl ;
  
} // ListAllFunctions()

void ListVariable() {
  int line = -1 ; 
  // cout << "我很快樂" << endl ; 
  // cout << g_name.at(2) << endl ; 
  string cut = g_name.at( 2 ).substr( 1, g_name.at( 2 ).length()-2 ) ;
  // cout << cut << endl ; 
  
  for ( int i = 0 ; i < g_name_list.size() ; i++ ) {
    if ( cut == g_name_list.at( i ).at( 1 ) ) 
      line = i ; 
  } // for()
  
  cout << "> " ; 
  
  if ( cut == "" ) {
    cout << "Statement executed ..." << endl ;
    g_th++; 
    return ; 
  } // if()
  
  if ( line != -1 ) {
    for ( int i = 0 ; i < g_name_list.at( line ).size() ; i++ ) {
      if (  g_name_list.at( line ).at( i ) != "[" && i != 0 )
        cout << " " ; 
      cout << g_name_list.at( line ).at( i )  ; 
      // if ( g_name_list.at( line ).at( i + 1 ) != "["  ) 
    } // for()
    
    cout << endl << "Statement executed ..." << endl ;
  } // if ()
  else {
    cout << "Statement executed ..." << endl ;     
  } // else 
   
} // ListVariable()

void ListFunction() {
  int line = -1 ; 
  int w_space = 0 ; 
  // cout << "我很快樂" << endl ; 
  // cout << g_name.at(2) << endl ; 
  string cut = g_name.at( 2 ).substr( 1, g_name.at( 2 ).length()-2 ) ;
  // cout << cut << endl ; 
  
  for ( int i = 0 ; i < g_func_list.size() ; i++ ) {
    if ( cut == g_func_list.at( i ).at( 1 ) ) 
      line = i ; 
  } // for()
  
  cout << "> " ; 
  
  if ( cut == "" ) {
    cout << "Statement executed ..." << endl ;
    return ; 
  } // if()
  
  if ( line != -1 ) {
    for ( int i = 0 ; i < g_func_list.at( line ).size() ; i++ ) { // pretty print

      if ( g_func_list.at( line ).at( i ) == "{" ) {
        w_space += 2 ; 
        cout << g_func_list.at( line ).at( i ) ;
        cout << endl ; 
        if ( i + 1 < g_func_list.at( line ).size() )
          if ( g_func_list.at( line ).at( i + 1 ) != "}" )
            for ( int i = 0 ; i < w_space ; i ++ ) 
              cout << " " ;  
        
      } // if()
      
      else if ( g_func_list.at( line ).at( i ) == "}" ) {
        w_space -= 2 ; 
        if ( i + 1 < g_func_list.at( line ).size() )
          if ( g_func_list.at( line ).at( i + 1 ) != "}" && g_func_list.at( line ).at( i - 1 ) != ";" && 
               g_func_list.at( line ).at( i - 1 ) != "}" )
            cout << endl ; 
  
        for ( int i = 0 ; i < w_space ; i ++ ) 
          cout << " " ;  
        cout << g_func_list.at( line ).at( i )  ;
  
        if ( i + 1 < g_func_list.at( line ).size() )
          cout << endl ;    
  
        if ( i + 1 < g_func_list.at( line ).size() )
          if ( g_func_list.at( line ).at( i + 1 ) != "}" )
            for ( int i = 0 ; i < w_space ; i ++ ) 
              cout << " " ;  
      } // if()
      
      else if ( g_func_list.at( line ).at( i ) == ";" ) {
        cout << g_func_list.at( line ).at( i ) ;
        cout << endl ;
        if ( i + 1 < g_func_list.at( line ).size() )
          if ( g_func_list.at( line ).at( i + 1 ) != "}" ) {
            for ( int i = 0 ; i < w_space ; i ++ ) 
              cout << " " ;  
          } // if()
      } // else if()
      else 
        cout << g_func_list.at( line ).at( i ) ;
      
      if ( i + 1 < g_func_list.at( line ).size() )
        if ( ( g_func_list.at( line ).at( i + 1 ) != "[" && g_func_list.at( line ).at( i + 1 ) != "(" ) ||
             g_func_list.at( line ).at( i ) == "while" || g_func_list.at( line ).at( i ) == "if"  ) {
          if ( g_func_list.at( line ).at( i ) != ";" && g_func_list.at( line ).at( i ) != "}" && 
               g_func_list.at( line ).at( i ) != "{" && g_func_list.at( line ).at( i + 1 ) != "--" &&
               g_func_list.at( line ).at( i + 1 ) != "++" && g_func_list.at( line ).at( i + 1 ) != ","  )
            cout << " " ;
        } // if()
    } // for() 
    
    cout << endl << "Statement executed ..." << endl ; 
  } // if()
  else {
    cout << "Statement executed ..." << endl ;
  } // else 
} // ListFunction()

void Save_if() {
  
  bool check_if = false ; 
  if ( g_func_rest != 1 && g_if == true ) {  
    for ( int i = 0 ; i < g_count_if.size() ; i++  ) {
      for ( int k = 0 ; k < g_name_list.size() && check_if == false ; k++ ) {
        if ( g_count_if.at( i ).data == g_name_list.at( k ).at( 1 ) ) 
          check_if = true ; 
      } // for()
      
      if ( check_if == false ) {
        g_tp.push_back( g_count_if.at( i ).type ) ;
        g_tp.push_back( g_count_if.at( i ).data ) ; 
        if ( g_count_if.at( i ).array != "\0" ) {
          g_tp.push_back( "[" ) ;
          g_tp.push_back( g_count_if.at( i ).array ) ;
          g_tp.push_back( "]" ) ;
        } // if ()
        
        g_name_list.push_back( g_tp ) ; 
      } // if()  
      
      g_tp.clear() ; 
      check_if = false ;
    } // for()
  } // if ()
  
} // Save_if()

int main() { 
  char temp ; // 讀取1個字元
  char next_temp ; 
  int start = 0 ; 
  int end = 0 ;   
  bool at_next = true ; 
  char title ; 
  Token_data token  ;
  int i = 0 ; 
  bool error_line = false ; 
  vector<string> temp_count ;
  Push_in() ; 
  
  string s = "fuck1999" ; 

  
  char title1 ; 
  cout << "Our-C running ..." << endl ;
  // while ( title != '\n' ) 
  title = getchar(); // 讀換行 
  title1 = getchar(); // 讀換行

  while ( scanf( "%c", &g_topic[i] ) == 1 ) { // 全部元件讀進topic  
    // if ( g_topic[i] != ' ' ) 
    i++;
  } // while
  
  for ( int i = 0 ; i < 1000 && g_topic[g_at] != '\0' && g_at < 5000 ; i++ ) {     
               
    Get_token( token, temp, next_temp, at_next ) ;
    
    if ( token.data != "\0" && g_topic[g_at] != ' ' && g_error_1 == false ) {
      token.th = i;
      g_scan.push_back( token ) ; 
    } // if()
    
    if ( g_error_char != EOF && g_error_char != '\0' && g_error_char != ' ' && g_error_1 == true ) {
      token.type = "not_defined";
      g_scan.push_back( token ) ; 
      // cout << "Unrecognized token with first char : '" << g_error_char << "'"<<  endl  ;
    } // if
    
    g_error_1 = false; 
    token.data = "" ; 
    token.type = "" ;
  } // for()
  
  /*
  for ( int i = 0 ; i < g_scan.size() - 1 ; i ++ ) {
    cout << i << " : " << g_scan.at( i ).data  ;
    cout << "." << g_scan.at( i ).type << endl ;  
  } // for()
  */
  while ( g_th < g_scan.size() - 1  && g_list != "Done();" ) {
    // if ( g_error_2 == false ) 
    g_small.push_back( s ) ; 
    g_count_ready.push_back( g_small ) ; 
    
    g_error_1 = false ;   
    g_error_2 = false ;
    g_error_3 = false ; 
       
    
    Get_next_token();
    // if ( g_line == 0 ) g_line = 1 ;
    
    
    if ( g_scan.at( g_th ).data != " " && g_scan.at( g_th ).data != "\n" && g_error_2 == false )  {
      
      Scanner() ; 
       
    } // if()
    
    /*
    if ( g_scan.at( g_th ).data != "\n" )
      for ( int i = 0 ; i < g_count.size() ; i ++ )
        cout << g_count.at(i) << endl ;
      // cout << g_func_name << endl ; 
    */
    /*
    if ( g_scan.at( g_th ).data != "\n" ) {
      cout << g_scan.at( g_th ).data << endl ; 
      if ( g_error_2 == true ) cout << "THERE IS ERROR!!!" << endl ; 
      else cout << "NO ERROR~" << endl ; 
    } // if()
    */
    
    if ( g_name.size() >= 1 && g_name.at( 0 ) == "ListVariable" && g_error_2 == false ) {
      ListVariable() ; 
      // g_th++ ; 
    } // if()
    
    else if ( g_name.size() >= 1 && g_name.at( 0 ) == "ListFunction" && 
         g_error_2 == false ) {
      ListFunction() ; 
    } // if()
    else if ( g_name.size() >= 1 && g_name.at( 0 ) == "ListAllVariables" && 
              g_error_2 == false  ) { // 印出所有已定義 
      ListAllVariables() ; 
    } // if()
    else if ( g_name.size() >= 1 && g_name.at( 0 ) == "ListAllFunctions" && 
              g_error_2 == false  ) { // 印出所有已定義 
      ListAllFunctions() ; 
    } // if()
    
    else if ( g_error_2 == false && g_list != "Done();" &&  g_scan.at( g_th ).data != "\n"  )  {
      
      if ( g_ds == 1 ) {
         
        if ( g_func_rest == 1 ) {     // 檢查本題func名稱是否是更新的 
          cout << "> " ;
          if ( Check_defined( g_func_name ) == true ) {            
            cout << "New definition of " ; 
            cout << g_func_name << "()" ; 
            cout << " entered ..." << endl  ;  
          } // if()
          else {
            cout << "Definition of " ; 
            cout << g_func_name << "()" ; 
            cout << " entered ..." << endl ;  
          } // else if()
        } // else if()
        
        if ( g_func_rest == 2 ) { // 是count
          cout << "> " ;
          for ( int i = 0 ; i < g_count.size() ; i ++ ) { // 檢查本題變數是否是更新的 
            if ( Check_defined( g_count.at( i ) ) == true ) {                
              cout << "New definition of " ; 
              cout << g_count.at( i ) ; 
              cout << " entered ..." << endl ;  
            } // if()
            else {               
              cout << "Definition of " ; 
              cout << g_count.at( i ) ;
              cout << " entered ..." << endl ;  
            } // else()
          } // for()
        } // if()
      } // if()
      
      
      

      Save_if(); 
      
    
      
      bool check_s = false ; 
      if ( g_ds == 1 && g_func_rest == 1 ) {  // 存func名稱 
        for ( int i = 0 ; i < g_func_list.size() ; i++ ) {
          if ( g_name.at( 1 ) == g_func_list.at( i ).at( 1 ) ) {
            check_s = true ;
            g_func_list.at( i ) = g_name ; 
          } // if() 
        } // for()
        
        if ( check_s == false )  
          g_func_list.push_back( g_name ) ; 
      } // if()
      
      int where = 1 ; 
      if ( g_ds == 1 && g_func_rest == 2 ) { // 存全域變數
        for ( int k = 0 ; k < g_count.size() ; k++ ) {
          temp_count.push_back( g_name.at( 0 ) );
          
          while ( g_name.at( where ) != ";" && g_name.at( where ) != ","  ) {
            temp_count.push_back( g_name.at( where ) ) ; 
            where ++ ;
          } // while

          for ( int i = 0 ; i < g_name_list.size() ; i++ ) {
            if ( g_count.at( k ) == g_name_list.at( i ).at( 1 ) ) {
              check_s = true ; 
              g_name_list.at( i ) = temp_count ; 
            } // if() 
          } // for()

          if ( check_s == false ) 
            g_name_list.push_back( temp_count ) ; 

          if ( g_name.at( where ) == "," ) where++ ;
          check_s = false ; 
          temp_count.clear();
        } // for 
      } // if()
      /*
      for ( int i = 0 ; i < g_name.size() ; i++ ) 
        cout << g_name.at(i) << endl ;  

      for ( int i = 0 ; i < g_count.size() ; i++ ) 
        cout << g_count.at(i) << endl  ;  
      */
      
      if ( g_ds == 2 ) {
        cout << "> Statement executed ..." << endl ;  
      } // if()
      
      // cout << "line: "  << g_line << endl ; 
      // cout << "印出來看 :" << endl << g_list << endl  ;
      // cout << "*****************************************" << endl ;
    } // else if()
    else if ( g_error_2 == true && g_list != "Done();" ) { // 有ERROR 
      error_line = true ;   
      // if ( g_line == 0 ) g_line = 1 ; 
      // if ( g_line == 0 ) g_line = 1 ; 
      if ( g_error_1 == true ) {
        cout << "> Line " << g_line << " : unrecognized token with first char : '" ;
        cout << g_scan.at( g_th ).data << "'" << endl;
        Get_next_line_token() ; 
      } // if()
      else if ( g_error_3 == false ) {
        cout << "> Line " << g_line << " : unexpected token : '" ;
        cout << g_scan.at( g_th ).data << "'" << endl;
        Get_next_line_token() ; 
      } // if()
      else if ( g_error_3 == true ) {
        cout << "> Line " << g_line << " : undefined identifier : '" ;
        cout << g_scan.at( g_th ).data << "'" <<  endl;
        Get_next_line_token() ; 
      } // if() 
    } // else if()
    // cout << "印出來看 :" << endl << g_list << endl  ;
    
    
    
    if ( g_list != "Done();" ) 
      g_list = "" ;  
    if ( g_th < g_scan.size() - 2 ) {
      if ( error_line == false  ) {  // 文法沒有錯誤 
        g_line = 0 ;                      // if 比較特別要另外處理 
        if ( g_in_if == true && g_th < g_scan.size() - 1 && g_scan.at( g_th+1 ).data == "\n" && 
             g_void == false ) {  // if 後面接換行 
          while ( g_scan.at( g_th+1 ).data == "\n"  && g_th < g_scan.size() - 1 ) {
            g_th++;
            g_line++;       
             
          } // while()
          // while ( g_scan.at(tp).data != "\n" ) ;
        } // if()
        
        else if ( g_in_if == true && g_th < g_scan.size() - 1 && 
                  g_scan.at( g_th+1 ).data != "\n" ) // IF後面接文法 
          g_line = 1 ;
        else if ( g_th < g_scan.size() - 1 && g_scan.at( g_th + 1 ).data != "\n" && 
                  g_in_if == false ) g_line = 1 ;
             
      } // if()
      else {  // 文法有錯誤 直接讀下一行 
        g_line = 1 ; 
      } // else()
    } // if()
    
    error_line = false ;
    
    // cout << g_th ;
    /*
    g_line = 0;
    
    if ( g_scan.at( g_th ).data == "\n" ) g_line++ ;
    */
    /*
    for ( int i = 0  ; i < g_count_small.size() ; i ++ ) 
      cout << g_count_small.at(i) << " "  ;         
    cout << endl ;  
    */
    
    // cout << g_scan.at(g_th).data << endl ; 

    
    // if ( g_func_rest  == 2 ) cout << " is two " << endl  ;
    // else cout << "is one " << endl ; 
    
    // if( g_func_rest == 1 ) cout << "***" << "function" << "***" << endl ;  
    // if( g_func_rest == 2 ) cout << "***" << "rest" << "***" << endl ;
    // cout << "我是豬豬" << endl ; 
    
    g_type = "" ; 
    g_data = "" ; 
    g_array = "" ; 
    g_void = false;  
    g_in_if = false ; 
    g_count_if.clear() ; 
    g_if = false ;  
    g_small.clear();
    g_c = 0 ; 
    g_count.clear() ; 
    g_count_small.clear() ;  
    g_count_ready.clear() ; 
    g_aldef_func_bool = false ;  
    g_func_rest = 0 ;  
    g_name.clear() ;    
    g_ds = 0 ; 
    g_al_defined = false ;  
    g_func_name = "" ; 
  } // while() 
  
  cout << "> Our-C exited ..." ;
  
} // main() 

