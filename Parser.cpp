#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>

using namespace std;
static int c = 0, count = 0, parse = 0;

struct Token 
    {
    	int id;
    	int typenum;
    	string name;
    	int pos;
    	int len;
    	string value;
    };
    
Token* tokens = new Token[1024];

vector<string> output;
    
void stmt();
void while_stmt();
void for_stmt();
void if_stmt();
void opt_else();
void assignment_stmt();
void output_stmt();
void expr(int a, int b);
void mult_expr(int a, int b);
void unary_expr(int a, int b);
void paren_expr(int a, int b);
void basic_expr(int a, int b);
void cond_expr(int a, int b);
void and_expr(int a, int b);
void eq_expr(int a, int b);
void cmp_expr(int a, int b);
void opt_cond_expr(int a, int b);
void opt_assign(int a, int b);
int parsing();
void match(string name);
void printing();

int main(int argc, char* argv[])
{
    string line = "";
    char ch;
    int tidcount = 1, out_flag = 0, p_flag = 0;
    int p = 0, k = 0;
    while (cin.get(ch))
    {
        line += ch;
    }
    

    
   
                for (; k < line.length();)
                {
                    string word = "";
                    
                    if(line[k] == 40) // for (
                    {
                    	tokens[count].id = tidcount;
                        tokens[count].typenum = 33;
                        tokens[count].name = "(";
                        tokens[count].pos = k;
                        tokens[count].len = 1;
                        tidcount++;
                        count++;
                        k++;
                    }
                    else if(line[k] == 41) // for )
                    {
                    	tokens[count].id = tidcount;
                        tokens[count].typenum = 34;
                        tokens[count].name = ")";
                        tokens[count].pos = k;
                        tokens[count].len = 1;
                        tidcount++;
                        count++;
                        k++;
                    }
                    else if (48 <= line[k] && line[k] <= 57)  //checking for an integer
                    {
                        while (line[k] >= 48 && line[k] <= 57 && line[k] != 46)
                        {
                            word += line[k];
                            k++;
                        }
                        if (line[k] == 46)   //if there is a decimal point in between the integers
                        {
                            word += line[k];
                            k++;
                            while (line[k] >= 48 && line[k] <= 57)
                            {
                                word += line[k];
                                k++;
                            }
                            tokens[count].id = tidcount;
                        	tokens[count].typenum = 4;
                        	tokens[count].name = "FLOAT";
                        	tokens[count].pos = k - word.length();
                        	tokens[count].len = word.length();
                        	tokens[count].value = word;
                            tidcount++;
                            count++;
                        }
                        else
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 3;
                        	tokens[count].name = "INT";
                        	tokens[count].pos = k - word.length();
                        	tokens[count].len = word.length();
                        	tokens[count].value = word;
                            tidcount++;
                            count++;
                        }
                    }
                    else if (line[k] == 46) // checking for a decimal point at the start
                    {
                        word += line[k];
                        k++;
                        if(line[k] >= 48 && line[k] <= 57)
                        {
		                    while (line[k] >= 48 && line[k] <= 57)
		                    {
		                        word += line[k];
		                        k++;
		                    }
		                    tokens[count].id = tidcount;
                        	tokens[count].typenum = 4;
                        	tokens[count].name = "FLOAT";
                        	tokens[count].pos = k - word.length();
                        	tokens[count].len = word.length();
                        	tokens[count].value = word;
		                    tidcount++;
		                    count++;
		                }
		                else
		                {
		                	tokens[count].id = tidcount;
                        	tokens[count].typenum = 100;
                        	tokens[count].name = "ERR4";
                        	tokens[count].pos = k - 1;
                        	tokens[count].len = 1;
		                	tidcount++;
		                	count++;
		                }	
		            }
                    else if (line[k] == 32 || line[k] == 9)     //checking for a whitespace
                    {
                        while (line[k] == 32 || line[k] == 9)
                        {
                            word += line[k];
                            k++;
                        }
                       
		                tidcount++;
		          
                    }
                    else if (line[k] == 34) // checking for quotation marks at the start
                    {
                        k += 1;
                        while (((line[k] >= 32 && line[k] <= 126) || line[k] == 9)
                        && line[k] != 34)
                        {
                        	if(line[k] == 92 && line[k + 1] == 110) // if it's a backslash followed by n
                        	{
                        		tokens[count].id = tidcount;
                        		tokens[count].typenum = 98;
                        		tokens[count].name = "ERR2";
                        		tokens[count].pos = k - word.length() - 1;
                        		tokens[count].len = word.length() + 1;
                                tidcount++;
                                count++;
                            	break;
                            }
                            if(line[k] == 92 && line[k + 1] == 34) // if it's a backslash followed by "
                        	{
                        		tokens[count].id = tidcount;
                        		tokens[count].typenum = 98;
                        		tokens[count].name = "ERR2";
                        		tokens[count].pos = k - word.length() - 1;
                        		tokens[count].len = word.length() + 1;
                                tidcount++;
                                count++;
                            	break;
                            }
                            word += line[k];
                            k++;
                        }
                        if (line[k] == 10)   // if there are no ending quotation marks by the end of the line
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 98;
                        	tokens[count].name = "ERR2";
                        	tokens[count].pos = k - word.length() - 1;
                        	tokens[count].len = word.length() + 1;
                            tidcount++;
                            count++;
                        }
                        else if(k == line.length())
                       	{
                       		tokens[count].id = tidcount;
                        	tokens[count].typenum = 98;
                        	tokens[count].name = "ERR2";
                        	tokens[count].pos = k - word.length() - 1;
                        	tokens[count].len = word.length() + 1;
                            tidcount++;
                            count++;
                        }
                        else if (line[k] == 34)  // if there are ending quotaion marks
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 2;
                        	tokens[count].name = "STR";
                        	tokens[count].pos = k - word.length() - 1;
                        	tokens[count].len = word.length() + 2;
                        	tokens[count].value = word;
                            tidcount++;
                            count++;
                            k++;
                        }
                        // checking if there is a bad character
                        else if ((line[k] >= 0 && line[k] <= 8) || (line[k] >= 11 && line[k] <= 31) || (line[k] >= 127 && line[k] <= 255))
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 98;
                        	tokens[count].name = "ERR2";
                        	tokens[count].pos = k - word.length() - 1;
                        	tokens[count].len = word.length() + 1;
                            tidcount++;
                            count++;
                        }
                    }
                    //checking if there is a single or consecutive bad characters
                    else if ((line[k] >= 0 && line[k] <= 8) || (line[k] >= 11 && line[k] <= 31) || (line[k] >= 127 && line[k] <= 255))
                    {
                        while ((line[k] >= 0 && line[k] <= 8) || (line[k] >= 11 && line[k] <= 31) || (line[k] >= 127 && line[k] <= 255))
                        {
                            word += line[k];
                            k++;
                        }
                        tokens[count].id = tidcount;
                        tokens[count].typenum = 99;
                        tokens[count].name = "ERR3";
                        tokens[count].pos = k - word.length();
                        tokens[count].len = word.length();
                        tidcount++;
                        count++;
                    }
                    else if (line[k] == 35)  // checking for a comment at the start
                    {
                    	while(line[k] != 10 && k != line.length())
                        {
                        	if((line[k] >= 0 && line[k] <= 8) || (line[k] >= 11 && line[k] <= 31) || (line[k] >= 127 && line[k] <= 255))
                        	{	
                        		tokens[count].id = tidcount;
                        		tokens[count].typenum = 99;
                        		tokens[count].name = "ERR3";
                        		tokens[count].pos = k;
                        		tokens[count].len = 1;
                        		tidcount++;
                        		count++;
                        	}
                            word += line[k];
                            k++;
                        }
                        
                        tidcount++;
                    
                    }
                    // checking if it's an underscore or a letter at the start
                    else if ((line[k] >= 65 && line[k] <= 90) ||
                    	(line[k] >= 97 && line[k] <= 122) || line[k] == 95)
                    {
                        int id_flag = 1;
                        word += line[k];
                        k++;
                        // checking if it's an underscore or a letter or a number before the end of line
                        while ((line[k] >= 65 && line[k] <= 90) ||
                       	 	(line[k] >= 97 && line[k] <= 122) || line[k] == 95 || (line[k] >= 48 && line[k] <= 57))
                        {
                            word += line[k];
                            // checking for for, while, if, else if the id didn't start with an underscore
                            if ((word == "for" || word == "while" || word == "if" || word == "else") && (!((line[k+1] >= 65 && line[k+1] <= 90) ||
                        				(line[k+1] >= 97 && line[k+1] <= 122) || line[k+1] == 95 || (line[k+1] >= 48 && line[k+1] <= 57))))
                            {
                                if (word == "for")
                                {
                                	tokens[count].id = tidcount;
                        			tokens[count].typenum = 8;
                        			tokens[count].name = "FOR";
                        			tokens[count].pos = k - word.length() + 1;
                        			tokens[count].len = word.length();
                        			tokens[count].value = word;
                                   
                                    tidcount++;
                                    count++;
                                    k++;
                                    id_flag = 0;
                                }
                                else if (word == "while")
                                {
                                	tokens[count].id = tidcount;
                        			tokens[count].typenum = 9;
                        			tokens[count].name = "WHILE";
                        			tokens[count].pos = k - word.length() + 1;
                        			tokens[count].len = word.length();
                        			tokens[count].value = word;
                                   
                                    tidcount++;
                                    count++;
                                    k++;
                                    id_flag = 0;
                                }
                                else if (word == "if")
                                {
                                	tokens[count].id = tidcount;
                        			tokens[count].typenum = 10;
                        			tokens[count].name = "IF";
                        			tokens[count].pos = k - word.length() + 1;
                        			tokens[count].len = word.length();
                        			tokens[count].value = word;
                                   
                                    tidcount++;
                                    count++;
                                    k++;
                                    id_flag = 0;
                                }
                                else if (word == "else")
                                {
                                	tokens[count].id = tidcount;
                        			tokens[count].typenum = 11;
                        			tokens[count].name = "ELSE";
                        			tokens[count].pos = k - word.length() + 1;
                        			tokens[count].len = word.length();
                        			tokens[count].value = word;
                                   
                                    tidcount++;
                                    count++;
                                    k++;
                                    id_flag = 0;
                                }
                            }
                            else
                            {
                                k++;
                            }
                        }
                        // flag to skip if it already tokenized for, while, if or else
                        if (id_flag == 1)
                        {
                            // if the bad character is a space
                            if (line[k] == 32 || line[k] == 9)
                            {
                            	tokens[count].id = tidcount;
                        		tokens[count].typenum = 1;
                        		tokens[count].name = "ID";
                        		tokens[count].pos = k - word.length();
                        		tokens[count].len = word.length();
                        		tokens[count].value = word;
                                
                                tidcount++;
                                count++;
                            }
                            // if the bad character is a symbol
                            else if ((line[k] >= 33 && line[k] <= 47) || (line[k] >= 58 && line[k] <= 64) || (line[k] >= 91 && line[k] <= 94) || line[k] == 96
                            || (line[k] >= 123 && line[k] <= 126))
                            {
                            	tokens[count].id = tidcount;
                        		tokens[count].typenum = 1;
                        		tokens[count].name = "ID";
                        		tokens[count].pos = k - word.length();
                        		tokens[count].len = word.length();
                        		tokens[count].value = word;
                               
                                tidcount++;
                                count++;
                            }
                            else if (k == line.length())
                            {
                            	tokens[count].id = tidcount;
                        		tokens[count].typenum = 1;
                        		tokens[count].name = "ID";
                        		tokens[count].pos = k - word.length();
                        		tokens[count].len = word.length();
                        		tokens[count].value = word;
                               
                                tidcount++;
                                count++;
                            }
                        }
                    }
                    // checking if it's a symbol that's not in the lexical specification at the start meaning a character not valid in the context
                    else if (line[k] == 36 || line[k] == 39 || line[k] == 63 
                    	|| line[k] == 64 || line[k] == 92 || line[k] == 94 || line[k] == 96 || line[k] == 126)
                    {
                    	tokens[count].id = tidcount;
                        tokens[count].typenum = 100;
                        tokens[count].name = "ERR4";
                        tokens[count].pos = k;
                        tokens[count].len = 1;
                        tidcount++;
                        count++;
                        k++;
                    }
                    //checking if it's a symbol in the lexical specification
                    else if (line[k] == 33 || line[k] == 37 || line[k] == 38 || (line[k] >= 42 && line[k] <= 45)
                    	|| line[k] == 47 || (line[k] >= 58 && line[k] <= 62) || line[k] == 91 || line[k] == 93 || line[k] == 123 || line[k] == 124 || line[k] == 125)
                    {
                        if (line[k] == 60 && line[k + 1] == 61)
                        {
                            word += line[k];
                            word += line[k+1];
                            k++;
                            tokens[count].id = tidcount;
                        	tokens[count].typenum = 29;
                        	tokens[count].name = "<=";
                        	tokens[count].pos = k - word.length() + 1;
                        	tokens[count].len = 2;
                        	
                            tidcount++;
                            count++;
                            k++;
                        }
                        else if (line[k] == 62 && line[k + 1] == 61)
                        {
                            word += line[k];
                            word += line[k+1];
                            k++;
                            tokens[count].id = tidcount;
                        	tokens[count].typenum = 30;
                        	tokens[count].name = ">=";
                        	tokens[count].pos = k - word.length() + 1;
                        	tokens[count].len = 2;
         
                            tidcount++;
                            count++;
                            k++;
                        }
                        else if (line[k] == 33 && line[k + 1] == 61)
                        {
                            word += line[k];
                            word += line[k+1];
                            k++;
                            tokens[count].id = tidcount;
                        	tokens[count].typenum = 31;
                        	tokens[count].name = "!=";
                        	tokens[count].pos = k - word.length() + 1;
                        	tokens[count].len = 2;
                            
                            tidcount++;
                            count++;
                            k++;
                        }
                        else if (line[k] == 58 && line[k + 1] == 61)
                        {
                            word += line[k];
                            word += line[k+1];
                            k++;
                            tokens[count].id = tidcount;
                        	tokens[count].typenum = 32;
                        	tokens[count].name = ":=";
                        	tokens[count].pos = k - word.length() + 1;
                        	tokens[count].len = 2;
                            
                            tidcount++;
                            count++;
                            k++;
                        }
                        else if (line[k] == 58 && line[k + 1] != 61)
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 100;
                        	tokens[count].name = "ERR4";
                        	tokens[count].pos = k;
                        	tokens[count].len = 1;
                        	tidcount++;
                        	count++;
                        	k++;
                        }
                        else if (line[k] == 33)
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 12;
                        	tokens[count].name = "!";
                        	tokens[count].pos = k;
                        	tokens[count].len = 1;
                           
                            tidcount++;
                            count++;
                            k++;
                        }
                        else if (line[k] == 37)
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 13;
                        	tokens[count].name = "%";
                        	tokens[count].pos = k;
                        	tokens[count].len = 1;
                            
                            tidcount++;
                            count++;
                            k++;
                        }
                        else if (line[k] == 38)
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 14;
                        	tokens[count].name = "&";
                        	tokens[count].pos = k;
                        	tokens[count].len = 1;
                           
                            tidcount++;
                            count++;
                            k++;
                        }
                        else if (line[k] == 42)
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 18;
                        	tokens[count].name = "*";
                        	tokens[count].pos = k;
                        	tokens[count].len = 1;
                            
                            tidcount++;
                            count++;
                            k++;
                        }
                        else if (line[k] == 43)
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 16;
                        	tokens[count].name = "+";
                        	tokens[count].pos = k;
                        	tokens[count].len = 1;
                            
                            tidcount++;
                            count++;
                            k++;
                        }
                        else if (line[k] == 44)
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 25;
                        	tokens[count].name = ",";
                        	tokens[count].pos = k;
                        	tokens[count].len = 1;
                            
                            tidcount++;
                            count++;
                            k++;
                        }
                        else if (line[k] == 45)
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 17;
                        	tokens[count].name = "-";
                        	tokens[count].pos = k;
                        	tokens[count].len = 1;
                            
                            tidcount++;
                            count++;
                            k++;
                        }
                        else if (line[k] == 47)
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 19;
                        	tokens[count].name = "/";
                        	tokens[count].pos = k;
                        	tokens[count].len = 1;
                            
                            tidcount++;
                            count++;
                            k++;
                        }
                        else if (line[k] == 59)
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 24;
                        	tokens[count].name = ";";
                        	tokens[count].pos = k;
                        	tokens[count].len = 1;
                            
                            tidcount++;
                            count++;
                            k++;
                        }
                        else if (line[k] == 60)
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 26;
                        	tokens[count].name = "<";
                        	tokens[count].pos = k;
                        	tokens[count].len = 1;
                            
                            tidcount++;
                            count++;
                            k++;
                        }
                        else if (line[k] == 61)
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 28;
                        	tokens[count].name = "=";
                        	tokens[count].pos = k;
                        	tokens[count].len = 1;
                            
                            tidcount++;
                            count++;
                            k++;
                        }
                        else if (line[k] == 62)
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 27;
                        	tokens[count].name = ">";
                        	tokens[count].pos = k;
                        	tokens[count].len = 1;
                            
                            tidcount++;
                            count++;
                            k++;
                        }
                        else if (line[k] == 91)
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 22;
                        	tokens[count].name = "[";
                        	tokens[count].pos = k;
                        	tokens[count].len = 1;
                            
                            tidcount++;
                            count++;
                            k++;
                        }
                        else if (line[k] == 93)
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 23;
                        	tokens[count].name = "]";
                        	tokens[count].pos = k;
                        	tokens[count].len = 1;
                            
                            tidcount++;
                            count++;
                            k++;
                        }
                        else if (line[k] == 123)
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 20;
                        	tokens[count].name = "{";
                        	tokens[count].pos = k;
                        	tokens[count].len = 1;
                            
                                tidcount++;
                                count++;
                                k++;
                        }
                        else if (line[k] == 125)
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 21;
                        	tokens[count].name = "}";
                        	tokens[count].pos = k;
                        	tokens[count].len = 1;
                              
                            tidcount++;
                            count++;
                            k++;
                        }
                        else if (line[k] == 124)
                        {
                        	tokens[count].id = tidcount;
                        	tokens[count].typenum = 15;
                        	tokens[count].name = "|";
                        	tokens[count].pos = k;
                        	tokens[count].len = 1;
                              
                            tidcount++;
                            count++;
                            k++;
                        }
                    } // end of last else if
                    else if(line[k] == 10)
                    {
                    	
                    	
                		tidcount++;
             
                		k++;
                	}
                } 
            	tokens[count].id = tidcount;
                tokens[count].name = "epsilon";
                // output the final line
                //cout << "\n" << "Totals: " << "len = " << p << ", tokens = " << tidcount << ", printed = " << p_flag << "\n";
               
          
  	cout << "\n";
    for(int t = 0; t < count; t++)
    {
    	if(tokens[t].typenum == 97 || tokens[t].typenum == 98 || tokens[t].typenum == 99 || tokens[t].typenum == 100)
    	{
    		cout << "Lex error\n";
    		return EXIT_SUCCESS;
    	}
    } 
    for(int t = 0; t < count; t++)
    {
    	if(tokens[t].typenum == 13 || tokens[t].typenum == 19 || tokens[t].typenum == 25)
    	{
    		cout << "Unimplemented error\n";
    		return EXIT_SUCCESS;
    	}
    } 
    parsing();            
}

int parsing()
{	
	if(tokens[c].name == "FOR" || tokens[c].name == "WHILE" || tokens[c].name == "IF" || tokens[c].name == "[" 
		|| (tokens[c].name == "ID" && tokens[c + 1].name == ":="))
	{
		stmt();
		output.push_back("</node></children>\n");
		output.push_back("</node>\n");
		printing();
	}
	else if(tokens[c].name == "epsilon")
	{	
		stmt();
		output.push_back("</node></children>\n");
		output.push_back("</node>\n");
		printing();
	}
	else
	{
		cout << "Parse error\n";
		return EXIT_SUCCESS;
	}
}


void stmt()
{
	output.push_back("<node><nt>stmt</nt><children>\n");
	if(tokens[c].name == "FOR")
	{
		for_stmt();
		output.push_back("</node></children>\n");
		output.push_back("</node>\n");
		stmt();
		output.push_back("</node></children>\n");
	}
	else if(tokens[c].name == "WHILE")
	{
		while_stmt();
		output.push_back("</node></children>\n");
		output.push_back("</node>\n");
		stmt();
		output.push_back("</node></children>\n");
	}
	else if(tokens[c].name == "IF")
	{
		if_stmt();
		output.push_back("</node></children>\n");
		output.push_back("</node>\n");
		stmt();
		output.push_back("</node></children>\n");
	}
	else if(tokens[c].name == "[")
	{
		output_stmt();
		output.push_back("</node></children>\n");
		output.push_back("</node>\n");
		stmt();
		output.push_back("</node></children>\n");
	}
	else if(tokens[c].name == "epsilon" || tokens[c].name == "}")
		match("epsilon");
	else if(tokens[c].name == "ID" && tokens[c + 1].name == ":=")
	{
		assignment_stmt();
		output.push_back("</node></children>\n");
		output.push_back("</node>\n");
		match(";"); output.push_back("</node>\n");
		stmt();
		output.push_back("</node></children>\n");
	}
	else 
	{
		cout << "Parse error\n";
		exit(0);
	}
}

void for_stmt()
{
	output.push_back("<node><nt>for_stmt</nt><children>\n");
	match("FOR"); output.push_back("</node>\n");
	match("("); output.push_back("</node>\n");
	int x = c;
	for(;x < count; x++)
	{
		if(tokens[x].name == ";")
		{
			opt_assign(c, x - 1);
			output.push_back("</node></children>\n");
			output.push_back("</node>\n");
			break;
		}
	}
	if(x == count)
	{
		cout << "Parse error\n";
		exit(0);
	}
	match(";");
	int y = c; output.push_back("</node>\n");
	for(;y < count; y++)
	{
		if(tokens[y].name == ";")
		{
			opt_cond_expr(c, y - 1);
			output.push_back("</node></children>\n");
			output.push_back("</node>\n");
			break;
		}
	}
	if(y == count)
	{
		cout << "Parse error\n";
		exit(0);
	}
	match(";"); output.push_back("</node>\n");
	int z = c;
	for(;z < count; z++)
	{
		if(tokens[z].name == "{")
		{
			opt_assign(c, z - 2);
			output.push_back("</node></children>\n");
			output.push_back("</node>\n");
			break;
		}
	}
	if(z == count)
	{
		cout << "Parse error\n";
		exit(0);
	}
	match(")"); output.push_back("</node>\n");
	match("{"); output.push_back("</node>\n");
	
	stmt();
	output.push_back("</node></children>\n");
	output.push_back("</node>\n");
	match("}");
}

void while_stmt()
{
	output.push_back("<node><nt>while_stmt</nt><children>\n");
	match("WHILE"); output.push_back("</node>\n");
	match("("); output.push_back("</node>\n");
	int x = c;
	for(;x < count; x++)
	{
		if(tokens[x].name == "{")
		{
			cond_expr(c, x-2);
			output.push_back("</node></children>\n");
			output.push_back("</node>\n");
			break;
		}
	}
	if(x == count)
	{
		cout << "Parse error\n";
		exit(0);
	}
	match(")"); output.push_back("</node>\n");
	match("{"); output.push_back("</node>\n");
	stmt();
	output.push_back("</node></children>\n");
	output.push_back("</node>\n");
	match("}");
}

void if_stmt()
{
	output.push_back("<node><nt>if_stmt</nt><children>\n");
	match("IF"); output.push_back("</node>\n");
	match("("); output.push_back("</node>\n");
	int x = c;
	for(;x < count; x++)
	{
		if(tokens[x].name == "{")
		{
			cond_expr(c, x - 2);
			output.push_back("</node></children>\n");
			output.push_back("</node>\n");
			break;
		}
	}
	if(x == count)
	{
		cout << "Parse error\n";
		exit(0);
	}
	match(")"); output.push_back("</node>\n");
	match("{"); output.push_back("</node>\n");
	stmt();
	output.push_back("</node></children>\n");
	match("}"); output.push_back("</node>\n");
	opt_else();
	output.push_back("</node></children>\n");
}

void opt_else()
{
	output.push_back("<node><nt>opt_else</nt><children>\n");
	if(tokens[c].name == "ELSE")
	{
		match("ELSE"); output.push_back("</node>\n");
		match("{"); output.push_back("</node>\n");
		stmt();
		output.push_back("</node></children>\n");
		output.push_back("</node>\n");
		match("}");
	}
	else
		match("epsilon");
}

void assignment_stmt()
{
	output.push_back("<node><nt>assignment_stmt</nt><children>\n");
	match("ID"); output.push_back("</node>\n");
	match(":="); output.push_back("</node>\n");
	int a = c;
	for(;a < count; a++)
	{
		if(tokens[a].name == "{")
		{
			expr(c, a - 2);
			output.push_back("</node></children>\n");
			break;
		}
		else if(tokens[a].name == ";")
		{
			expr(c, a - 1);
			output.push_back("</node></children>\n");
			break;
		}
	}
	if(a == count)
	{
		cout << "Parse error\n";
		exit(0);
	}
}

void output_stmt()
{
	output.push_back("<node><nt>output_stmt</nt><children>\n");
	match("["); output.push_back("</node>\n");
	int a = c;
	for(;a < count; a++)
	{
		if(tokens[a].name == "]")
		{
			expr(c, a - 1);
			output.push_back("</node></children>\n");
			output.push_back("</node>\n");
			break;
		}
	}
	if(a == count)
	{
		cout << "Parse error\n";
		exit(0);
	}
	match("]"); output.push_back("</node>\n");
	match(";");
}

void expr(int a, int b)
{
	int end = b;
	output.push_back("<node><nt>expr</nt><children>\n");
	for(; b >= a; b--)
	{
		if(tokens[b].name == "+")
		{
			expr(c, b - 1);
			output.push_back("</node></children>\n");
			output.push_back("</node>\n");
			match("+"); output.push_back("</node>\n");
			mult_expr(b + 1, end);
			output.push_back("</node></children>\n");
			//output.push_back("</node>\n");
			break;
		}
	}
	if(b < a)
	{
		mult_expr(a, end);
		output.push_back("</node></children>\n");
	}
}

void mult_expr(int a, int b)
{
	int end = b;
	output.push_back("<node><nt>mult_expr</nt><children>\n");
	for(; b >= a; b--)
	{
		if(tokens[b].name == "*")
		{
			mult_expr(c, b - 1);
			output.push_back("</node></children>\n");
			output.push_back("</node>\n");
			match("*"); output.push_back("</node>\n");
			unary_expr(b + 1, end);
			output.push_back("</node></children>\n");
			break;
		}
	}
	if(b < a)
	{
		unary_expr(a, end);
		output.push_back("</node></children>\n");
	}
}

void unary_expr(int a, int b)
{
	output.push_back("<node><nt>unary_expr</nt><children>\n");
	if(tokens[c].name == "!")
	{
		match("!"); output.push_back("</node>\n");
		expr(c, b);
		output.push_back("</node></children>\n");
	}
	else if(tokens[c].name == "+")
	{
		match("+");
		expr(c, b);
	}
	else if(tokens[c].name == "-")
	{
		match("-");
		expr(c, b);
	}
	else
	{
		paren_expr(a, b);
		output.push_back("</node></children>\n");
	}
}

void paren_expr(int a, int b)
{
	output.push_back("<node><nt>paren_expr</nt><children>\n");
	if(tokens[c].name == "(")
	{
		match("(");
		expr(a, b);
		match(")");
	}
	else
	{
		basic_expr(a, b);
		output.push_back("</node></children>\n");
	}
}

void basic_expr(int a, int b)
{
	output.push_back("<node><nt>basic_expr</nt><children>\n");
	if(a == b)
	{
		if(tokens[c].name == "ID")
			match("ID");
		else if(tokens[c].name == "STR")
			match("STR");
		else if(tokens[c].name == "INT")
			match("INT");
		else if(tokens[c].name == "FLOAT")
			match("FLOAT");
	}
	else
	{
		cout << "Parse error\n";
		parse = 1;
		exit(0);
	}
}

void cond_expr(int a, int b)
{
	int end = b;
	output.push_back("<node><nt>cond_expr</nt><children>\n");
	for(; b >= a; b--)
	{
		if(tokens[b].name == "|")
		{
			cond_expr(c, b - 1);
			output.push_back("</node></children>\n");
			output.push_back("</node>\n");
			match("|"); output.push_back("</node>\n");
			and_expr(b + 1, end);
			output.push_back("</node></children>\n");
			break;
		}
	}
	if(b < a)
	{
		and_expr(c, end);
		output.push_back("</node></children>\n");
	}
}

void and_expr(int a, int b)
{
	int end = b;
	output.push_back("<node><nt>and_expr</nt><children>\n");
	for(; b >= a; b--)
	{
		if(tokens[a].name == "&")
		{
			and_expr(c, b - 1);
			output.push_back("</node></children>\n");
			output.push_back("</node>\n");
			match("&"); output.push_back("</node>\n");
			eq_expr(b + 1, end);
			output.push_back("</node></children>\n");
			break;
		}
	}
	if(b < a)
	{
		eq_expr(a, end);
		output.push_back("</node></children>\n");
	}
}

void eq_expr(int a, int b)
{
	int end = b;
	output.push_back("<node><nt>eq_expr</nt><children>\n");
	for(; b >= a; b--)
	{
		if(tokens[b].name == "=")
		{
			eq_expr(a, b - 1);
			output.push_back("</node></children>\n");
			output.push_back("</node>\n");
			match("="); output.push_back("</node>\n");
			cmp_expr(b + 1, end);
			output.push_back("</node></children>\n");
			break;
		}
		else if(tokens[b].name == "!=")
		{
			eq_expr(a, b - 1);
			output.push_back("</node></children>\n");
			output.push_back("</node>\n");
			match("!="); output.push_back("</node>\n");
			cmp_expr(b + 1, end);
			output.push_back("</node></children>\n");
			break;
		}
	}
	if(b < a)
	{
		cmp_expr(a, end);
		output.push_back("</node></children>\n");
	}
}

void cmp_expr(int a, int b)
{
	int end = b;
	output.push_back("<node><nt>cmp_expr</nt><children>\n");
	for(; b >= a; b--)
	{
		if(tokens[b].name == "<")
		{
			cmp_expr(a, b - 1);
			output.push_back("</node></children>\n");
			output.push_back("</node>\n");
			match("<"); output.push_back("</node>\n");
			expr(b + 1, end);
			output.push_back("</node></children>\n");
			break;
		}
		else if(tokens[b].name == ">")
		{
			cmp_expr(a, b - 1);
			output.push_back("</node></children>\n");
			output.push_back("</node>\n");
			match(">"); output.push_back("</node>\n");
			expr(b + 1, end); 
			output.push_back("</node></children>\n");
			break;
		}
		else if(tokens[b].name == "<=")
		{
			cmp_expr(a, b - 1);
			output.push_back("</node></children>\n");
			output.push_back("</node>\n");
			match("<="); output.push_back("</node>\n");
			expr(b + 1, end);
			output.push_back("</node></children>\n");
			break;
		}
		else if(tokens[b].name == ">=")
		{
			cmp_expr(a, b - 1);
			output.push_back("</node></children>\n");
			output.push_back("</node>\n");
			match(">="); output.push_back("</node>\n");
			expr(b + 1, end);
			output.push_back("</node></children>\n");
			break;
		}
	}
	if(b < a)
	{
		expr(a, end);
		output.push_back("</node></children>\n");
	}
}

void opt_cond_expr(int a, int b)
{
	output.push_back("<node><nt>opt_cond_expr</nt><children>\n");
	if(tokens[a].name == ";")
	{
		match("epsilon");
	}
	else
	{
		cond_expr(a, b);
		output.push_back("</node></children>\n");
	}
}

void opt_assign(int a, int b)
{
	output.push_back("<node><nt>opt_cond_expr</nt><children>\n");
	if(tokens[a].name == ")" || tokens[a].name == ";")
	{
		match("epsilon");
	}
	else
	{
		assignment_stmt();
		output.push_back("</node></children>\n");
	}
}

void match(string ttype)
{	
	if(ttype == "epsilon" && tokens[c].name == "epsilon")
	{
		output.push_back("<node><epsilon></epsilon>\n");
		c++;
	}
	else if(ttype == "epsilon" && (tokens[c].name == ")" || tokens[c].name == ";" || tokens[c - 1].name == "}" || tokens[c].name == "}"))
	{
		output.push_back("<node><epsilon></epsilon>\n");
	}
	//if there are new line in between
	else if(ttype == "epsilon" && (!(tokens[c].name == ")" || tokens[c].name == ";" || tokens[c].name == "epsilon" || tokens[c - 1].name == "}")))
	{
		output.push_back("<node><epsilon></epsilon>\n");
		c++;
	}
	else if(tokens[c].name == ttype && tokens[c].value.empty()) //when the matched token has no value
	{
		output.push_back("<node><id>" + to_string(tokens[c].id) + "</id><typenum>" + to_string(tokens[c].typenum) + "</typenum><typename>" + tokens[c].name
			+ "</typename><position>" + to_string(tokens[c].pos) + "</position><length>" + to_string(tokens[c].len) + "</length>\n");
		c++;
	}
	else if(tokens[c].name == ttype)
	{
		output.push_back("<node><id>" + to_string(tokens[c].id) + "</id><typenum>" + to_string(tokens[c].typenum) + "</typenum><typename>" + tokens[c].name
			+ "</typename><position>" + to_string(tokens[c].pos) + "</position><length>" + to_string(tokens[c].len)
			+ "</length><value>" + tokens[c].value + "</value>\n");
		c++;
	}
	else
	{
		cout << "Parse error\n";
		exit(0);
	}
}

void printing()
{
	for(int i = 0; i < output.size(); i++)
	{
		cout << output.at(i);
	}
}
		
		
		
	
	
	
		
	
		
	
	
	
	
			
	
	
		
	
	
	
	
		
	
	
	
	
	
		
		
    
    
