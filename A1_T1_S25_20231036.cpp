// File: A1_T1_25_20231036.cpp
// Purpose: The program combines string manipulation, recursion, binary number generation, and phishing email scanning into
// an interactive tool for educational purposes in c++ .
// Author: Passant Shaaban Abdelazim Mohamed
// Section:25
// ID:20231036
// Date: 10 Oct 2024
// Detailed explaination: 
/* This program contains four main problems:

1. Split Function: Splits a given string into substrings based on a specified delimiter and returns a list of substrings.
   
2. Teddy Bear Game: A recursive game that determines if it's possible to win by reaching exactly 42 teddy bears from a starting number, using specific game rules (divide by 2, subtract a product of digits, or subtract 42).

3. Binary Numbers:
   - Converts a decimal number into its binary representation.
   - Generates all possible binary numbers of a given length `k` with a specified prefix.

4. Phishing Keyword Scanner: Scans an email file for common phishing keywords, counts occurrences, and assigns points to generate a total score based on the keywords found.

The program includes input validation for each problem to ensure proper user input.
*/

# include <iostream>
# include <vector>
# include <stack>
# include <fstream>
# include <map>
# include <filesystem>
using namespace std;

// the split function 
vector<string> split(string target, string delimiter){
    
    // a result vector to store substrings in it
    vector<string> result ;

    // intializing start and end positions
    size_t start = 0 ;  
    size_t end = 0 ;

    // Loop till the delimiter is not found 
    while ( (end = target.find(delimiter,start)) != string::npos){
        // storing the substring
        
        result.push_back(target.substr(start,end-start)) ;
        
        // giving the start a new position
        start = end + delimiter.length() ; 
    }

    // The last substring
    result.push_back(target.substr(start)) ;

   // Returning the result vector
   return result;
}


// the teddy bear game 
bool bear(int n){
    
    // Base case1: if we have less than 42, it's not possible to win the game
    if (n < 42){
        return false;
    }
    
    // Base case2: if we have exactly 42 bears, we have won the game
    if (n == 42){
        return true;
    }

   
    // Recursively check if we can win with half the bears
        if( n % 2 == 0 ){
            if( bear(n/2) ){
                return true ;
            } 
        }
    
    // Recursively check if we can win with the remaining bears after subtraction 
        if( n%3==0 || n%4==0 ){
            int last_digit = n%10 ;
            int next_to_last = (n%100) /10 ;
            int bears_to_give = last_digit * next_to_last;
            // Ensure we subtract a positive number
            if( bears_to_give>0 && bear( n -  bears_to_give ) ){
                return true;
            }  
        }

    // Recursively check if we can win with fewer 42 bears
        if( n%5 == 0 ){
            if(bear( n - 42 )){
                return true;
            }
            
        }

    // If none of the above strategies work
    return false;
   
}

// Function to represent binary numbers
static void binaryPrint(int n){
    if (n < 0){

    // If the input is negative, loop till the user enter a positive integer
        while ( n<0 ){
        cout << "Input should be non-negative, try again" <<endl ;
        cin >> n ;
        }
    }

    if (n == 0){
        cout << '0' ;
        return;
    }

    // To store the reminder during binary conversion
    int reminder;

    // To store binary digits
    stack<int> StoreBinary ;

    // Loop to convert the number to binary
        while (n>0){
        // Getting and storing the ramainder
            reminder = n%2 ;
            StoreBinary.push(reminder); 
        // Update n by divide by two     
            n = n/2 ;
        }

    // Loop to print binary digits
        while( ! StoreBinary.empty()){

            cout << StoreBinary.top();
        // Remove the top element from the stack    
            StoreBinary.pop();
        }

        cout << endl;   

    return;
}

// Function to generate all binary numbers of length k with a given prefix
static void numbers(string prefix, int k){
    
    // Ensure that the input is a non-negative integer
      if (k < 0){
        while ( k<0 ){
        cout << "Input should be non-negative, try again" <<endl ;
        cin >> k ;
        }
    } 
    // Base case: if k reaches 0, print the current prefix which  includes the possible combinations of binary
     if (k == 0){
        cout << prefix <<endl ;
        return;
    }
    
    // Recursively generate binary numbers with an additional '0' or '1'
    numbers( prefix + "0" , k-1 ) ;
    numbers( prefix + "1" , k-1 ) ;
    
   
}

// Function to scan phishing a file for phishing keywords
void phishing(string path){
    
    // Check path validation
    if(!std::filesystem::exists(path)){
        cout << "Error: this file does not exist. Please enter a valid file path" <<endl ;
        return;
    }

   // Map containing phishing keywords and their corresponding values 
    map<string,int> scan_map= {
        {"congrats!",2} , {"reward",4} , {"offer",4} , {"click",6} , {"register now",4} , {"device at risk",6} ,
        {"hurry up",4} , {"check",4} , {"link",6} , {"free" ,6} , {"southwest airlines",4} , {"mcafee",4} , {"walmart",4} ,
        {"your payment was declined",6} , {"account" ,6} , {"netflix" ,6} , {"win",6} , {"verify",4} , 
        {"please visit here",6} , {"someone tried to log in to your account",6} , {"offering",4} , {"gift",6} , {"congratulations!",2},
        {"attention",4} , {"harvard journalism professorship",6} , {"update your personal information",6} , {"prizes",6} , {"iphone",6},
        {"exclusive reward",6} , {"subscription",4} } ;
    

    fstream myfile ;

   // Open file to write an email
    myfile.open(path,ios::out) ;

    if ( myfile.is_open()){
        myfile << "Subject: Important Account Verification Required\n"
               << "Dear Customer,\n\n"
               << "We noticed unusual activity in your account. Please verify your account immediately to avoid suspension. "
               << "Click the link below to confirm your details.\n\n"
               << "http://fakebank.com/account-verification\n\n"
               << "If you do not verify within 24 hours, your account will be permanently locked.\n\n"
               << "Thank you,\nThe Bank Team";        
    
    // Display an error message if the file couldn't be opened 
    }else{
        cout << "Error, can't open the file to write";
        return;
    }
    myfile.close();

    // Open the file for phishing keywords scan 
    myfile.open(path,ios::in) ;
    if( !myfile.is_open()){
        cout << "Error, can't open the file to read";
        return;
    }
    //Reading the entire file content into a string
    string file_content((istreambuf_iterator<char>(myfile)), istreambuf_iterator<char>());
    myfile.close();

    int total_points = 0 ;
    // Loop through fishing keywords map 
    for( auto pair : scan_map){
        string keyword = pair.first;
        int keyword_points = pair.second;
        int occur = 0 ;
        size_t start = 0 ;

    // Search for the current keyword in the file
        while( file_content.find(keyword,start) != string::npos){
            occur++ ;
        // Update the starting position for the next search 
            start = file_content.find(keyword,start) + keyword.length() ;
        }

        // If the keyword exists in the email content, print it's data 
        if( occur > 0 ){
        cout <<"'" <<keyword <<"'" <<" Found: " <<occur  << " - total points for it: " <<keyword_points*occur <<endl <<endl ;
        total_points += (keyword_points*occur);
        }
    }

    // Print the total points for the entire email
    cout << "Total points for the entire email: " <<total_points <<endl;
      
      return;
    }
    
    bool isValidDigit(const string &input){                                                                           
        for( char c : input ){
            if(!isdigit(c)){
                return false;
            }
        }
        return true;
    }

    int getValidInput(){
        string input;
        while(true){
            cout << "Enter a number: " <<endl;
            cin >> input;
            if( isValidDigit(input) ){
                return stoi(input);
            }else{
                cout << "Invalid input, please enter a number" <<endl;
            }
        }
    }
 
// The main function
int main(){

    while (true){
    // Display program menu
        cout<<endl;
        cout << "Choose the number of the problem you want to solve: " <<endl
        << "1. Split"                                                  <<endl
        << "2. One binary number , Printing many numbers"              <<endl 
        << "3. Teddy bear"                                             <<endl 
        << "4. Phishing scan"                                          <<endl 
        << "5. Exit"                                                   <<endl; 

        int prob_num ;
        string first_input ;
        cin >> first_input ;
        cin.ignore();
    // Ensure the input is valid
       while(! isValidDigit(first_input) ){
        first_input = to_string(getValidInput());
       }
       
       prob_num = stoi(first_input) ;
       
    // Ensure the user choice is available   
        while ( (prob_num != 1) && (prob_num != 2) && (prob_num != 3) && (prob_num !=4) && (prob_num !=5) ){
            cout<< "Your input doesn't match the available choices, try again! " <<endl ;
            prob_num = getValidInput() ;
        }
        
    // Implement the split function
    if ( prob_num == 1 ){
        cout << "Enter the message you want to split" << endl ;
        string target , delimiter ;
        cin.ignore();
        getline(cin , target) ;
        cout << "Enter a delimiter" << endl ;
        getline(cin,delimiter) ;
        cout<<endl;
        // Vector to store substrings
        vector<string> result = split(target,delimiter);
        for( int i=0 ; i<result.size() ; i++ ){
            cout <<"'" << result[i] <<"'"   ;

            if ( i != result.size()-1 ){
                cout << "," ;
            }
        }
        
    // Implement the teddy bear function
    }else if( prob_num == 3 ){

        cout << "Enter the number of bears: " <<endl ;
        string num;
        cin >> num;

       // input validation
       while(! isValidDigit(num) ){
        num = to_string(getValidInput());
       }
        int n = stoi(num) ;

        if(bear(n)){
            cout << "True" <<endl ;
        }else{
            cout << "False" <<endl ;
        }

    // Implement binary function
    }else if( prob_num == 2 ){

        string prob2_menu;
        // Display problem two menu
        cout<< "Choose 1 or 2" <<endl          
            << "1. One binary number" <<endl
            << "2. Many binary numbers" <<endl;
        cin >> prob2_menu ;

       // input validation
       while(! isValidDigit(prob2_menu) ){
        prob2_menu = to_string((getValidInput()));
       }
       int One_Or_Many = stoi(prob2_menu) ;

        // Ensure the user input is available in menu      
        while ( One_Or_Many != 1 && One_Or_Many != 2 ){
            cout << "Invalid input, try again " <<endl ;
            One_Or_Many = getValidInput() ;
        }
        
        // Implement binary representation
        if ( One_Or_Many == 1 ){
        cout << "Enter decimal number to convert into binary: " <<endl ;
        string num;
        cin >> num;

       while(! isValidDigit(num) ){
        num = to_string(getValidInput());
       }
        int n = stoi(num);
        binaryPrint(n) ;
        
        // Implement binary combinations
        }else if( One_Or_Many == 2 ){
                                                   
            string prefix;
            cout << "Enter prefix :" <<endl ;
            cin >> prefix ;

            cout << "Enter the number of binary digits to generate:" <<endl ;
            string suffix ;
            cin >> suffix;

            while(! isValidDigit(suffix) ){
                suffix = to_string(getValidInput());
            }
           
            int k = stoi(suffix) ;
            numbers(prefix , k);
        }
    
    // Implement phishing scan function
    }else if( prob_num == 4){
        string path ;
        cout<<"Enter file path with the extension" <<endl;
        cin>>path ;

        // Ensure the file path is valid
        while( !std::filesystem::exists(path) ){
            cout << "Invalid file path. Please enter a valid file path" <<endl;
            cin >> path;
        }

        phishing(path);

    // Exit program    
    }else if( prob_num == 5){
        cout << "Thank you for using my program";
        break;
    }
    } 

   return 0;

} 