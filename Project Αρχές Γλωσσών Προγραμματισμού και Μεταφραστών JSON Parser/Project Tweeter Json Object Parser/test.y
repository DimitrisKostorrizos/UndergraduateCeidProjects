%{
#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


void yyerror(char const *S);
extern int yylineno;
extern char* yytext;
extern FILE *yyin;
extern FILE *yyout;
int yylex(void);
char* months[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
char* days[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
int tweet_id_array_size = 0;
int tweet_id_array_max_size = 10;
int *tweet_id;
int counter;
long long int id_string;
long long int *tweet_id_string;
int tweet_id_string_array_size = 0;
int tweet_id_string_array_max_size = 10;
char* input_string;
char* split_string;
char* retweeted_tweet_text;
char* retweeted_tweet_name;
int extended = 1;
int extended_tweet_length;
int hashtag_counter = 0;
char* full_text;
char* indice_text;
int indice_tuple_start;
int indice_tuple_end;
int hashtag_parsed = 0;
%}
%define parse.error verbose

%union 
{
    float real;
	int number;
    char *string;
	double scien;
}

%token	<string> STRING;
%token	<number> SIGN;
%token	<number> UNSIGN;
%token	<real>	REAL;
%token	<string> true;
%token	<string> false;
%token	<string> null;
%type <string> double_dot;
%type <string> left_bracket;
%type <string> right_bracket;
%type <string> left_curly_bracket;
%type <string> right_curly_bracket;
%type <string> comma;
//%type <string> elements; generic_elements contains this rule
%type <string> generic_elements;
%type <string> generic_values;
%type <string> boolean;
%type <string> user_screen_name_field;
%type <string> retweeted_tweet_text_field;
%type <string> retweet_object;
%type <string> retweeted_tweet_object;
%type <string> retweeted_status_text_field;
%type <string> retweeted_status_screen_name_field;
%type <string> retweet_user_screen_name_field;
%type <string> retweeted_status_object;
%type <string> retweeted_status_user_field;
%type <string> retweeted_tweet_user_field;
%type <string> tweet_created_at_field;
%type <string> tweet_id_string_field;
%type <string> tweet_text_field;
%type <string> tweet_user_field;
%type <string> user_location_field;
%type <string> user_id_field;
%type <string> user_name_field;
%type <string> user_attributes;
//%type <string> number_elements; generic_elements contains this rule
%type <string> number;
%type <string> scientific;
%type <string> epsilon;
%type <string> extended_tweet_attributes;
%type <string> extended_tweet;
%type <string> truncated_field;
%type <string> display_text_field;
%type <string> unsign_tuple;
%type <string> extended_tweet_fields;
%type <string> full_text_field;
%type <string> extended_tweet_display_text_range;
%type <string> extended_tweet_unsign_tuple;
%type <string> extended_tweet_text_field;
%type <string> entities_field;
%type <string> hashtags;
%type <string> indice;
%type <string> indice_array;
%type <string> indice_tuple;
%type <string> entities;
%type <string> indice_text_field;
%%

program : json_attributes
		| program json_attributes
    ;

json_attributes : extended_tweet_object { fprintf(yyout,"%s", "\n");}
				| retweet_object { fprintf(yyout,"%s", "\n");}
				| tweet_object { fprintf(yyout,"%s", "\n");}
				| generic_array { fprintf(yyout,"%s", "\n");}
	;

/*string_array : left_bracket elements right_bracket { fprintf(yyout,"%s%s%s", $1, $2, $3); } generic_elements, generic_array contains this rules
	;

elements : STRING { sprintf($$,"%s", $1); }
		 | STRING comma elements { sprintf($$,"%s%s%s", $1, $2, $3); }
	;

number_array : left_bracket number_elements right_bracket { fprintf(yyout,"%s%s%s", $1, $2, $3); }  
	;

number_elements : number { sprintf($$,"%s", $1); }
		| number comma number_elements { sprintf($$,"%s%s%s", $1, $2, $3); }		 
	;		*/

double_dot : ':' { $$ = ":"; }
	;

epsilon : 'e' { $$ = "e"; }
	;

left_bracket : '[' { $$ = "["; }
	;
	
right_bracket : ']' { $$ = "]"; }
	;
	
left_curly_bracket : '{' { $$ = "{\n"; }
	;
	
right_curly_bracket : '}' { $$ = "\n}"; } 
	;

comma : ',' { $$ = ","; }
	;
	
boolean : true { $$ = strdup("true");  }
		| false { $$ = strdup("false");  }
	;
	
generic_array : left_bracket generic_elements right_bracket  { fprintf(yyout,"%s%s%s", $1, $2, $3); }
	;
	
generic_elements : generic_values { sprintf($$,"%s", $1); }
		| generic_values comma generic_elements	 { sprintf($$,"%s%s%s", $1, $2, $3); }
	;
	
generic_values : number { sprintf($$,"%s", $1); }
				| STRING { sprintf($$,"%s", $1); }
				| null { $$ = strdup("null"); }
				| boolean { sprintf($$,"%s", $1); }
	;

extended_tweet_object : left_curly_bracket extended_tweet_attributes extended_tweet right_curly_bracket
														{
															extended = 1;
															hashtag_counter = 0;
															hashtag_parsed = 0;
															char* printf_string;
															asprintf(&printf_string,"%s%s\n%s%s\n", $1, $2, $3, $4);
															int left_bracket_counter = 0;
															int right_bracket_counter = 0;
															for(int i = 0; i < strlen(printf_string); i++)
															{
																if(printf_string[i] == '{')
																{
																	left_bracket_counter++;
																}
																if(printf_string[i] == '}')
																{
																	right_bracket_counter++;
																}
																printf("%c",printf_string[i]);
																if(printf_string[i] == '\n')
																{
																	int j;
																if(i+1 < strlen(printf_string) && printf_string[i+1] == '}')
																{
																	for(j = 0; j < left_bracket_counter - right_bracket_counter - 1; j++)
																	{
																		printf("\t");
																	}
																}
																else
																{
																	for(j = 0; j < left_bracket_counter - right_bracket_counter; j++)
																	{
																		printf("\t");
																	}
																}
															}
														}		
													}
	;

extended_tweet_attributes : tweet_created_at_field tweet_id_string_field truncated_field extended_tweet_text_field 
														{
															sprintf($$,"%s\n%s\n%s\n%s", $1, $2, $3, $4);
														}
	;

extended_tweet_text_field :	STRING double_dot STRING comma
								{ 
									if(strcmp("\"text\"",$1) != 0)
									{
										fprintf(stderr,"Error in line: %d\nInvalid extended tweet text field.\n", yylineno);
										exit(1);
									}
									if((strlen($3)>140))
									{
										fprintf(stderr,"Error in line: %d\nExtended tweet text field must have maximum 140 characters.\n", yylineno);
										exit(1);
									}
									sprintf($$, "%s %s %s%s", $1, $2, $3, $4);
								}
	;

truncated_field : STRING double_dot boolean comma display_text_field
									{
										if(strcmp("\"truncated\"", $1) != 0)
										{
											fprintf(stderr,"Error in line: %d\nInvalid extended tweet truncated field.\n", yylineno);
											exit(1);
										}
										if(strcmp("false",$3) == 0)
										{
											extended = 0;
										}
										sprintf($$,"%s %s %s%s\n%s", $1, $2, $3, $4, $5);
									}
	;

display_text_field : STRING double_dot unsign_tuple comma
														{
															if(strcmp("\"display_text_range\"", $1) != 0)
															{
																fprintf(stderr,"Error in line: %d\nInvalid extended tweet display text range field.\n", yylineno);
																exit(1);
															}
															sprintf($$,"%s %s %s%s", $1, $2, $3, $4);
														}
	;

unsign_tuple : left_bracket UNSIGN comma UNSIGN right_bracket 
												{ 
													if(($2 != 0) || ($4>140) || (extended == 0))
													{
														fprintf(stderr,"Error in line: %d\nInvalid extended tweet display text range tuple field.\n", yylineno);
														exit(1);
													}
													char tuple[9];
													sprintf(tuple,"%s%d%s%d%s", $1, $2, $3, $4, $5);
													$$ = strdup(tuple); 
												}  
			|			
				{
					if(extended == 1)
					{
						fprintf(stderr,"Error in line: %d\nInvalid extended tweet format.\n", yylineno);
						exit(1);
					}
				}
	;

extended_tweet : STRING double_dot left_curly_bracket extended_tweet_fields entities right_curly_bracket
														{
															if(strcmp("\"extended_tweet\"", $1) != 0)
															{
																fprintf(stderr,"Error in line: %d\nInvalid extended tweet field.\n", yylineno);
																exit(1);
															}
															sprintf($$,"%s %s\n%s%s\n%s%s", $1, $2, $3, $4, $5, $6);
														}
	;

extended_tweet_fields : full_text_field extended_tweet_display_text_range
												{
													sprintf($$,"%s\n%s", $1, $2);
												}
	;

full_text_field : STRING double_dot STRING comma
									{
										if(strcmp("\"full_text\"", $1) != 0)
										{
											fprintf(stderr,"Error in line: %d\nInvalid extended tweet full text field.\n", yylineno);
											exit(1);
										}
										full_text = strdup($3);
										int index = 0;
										while(full_text[index]!='\0')
										{
											if(full_text[index] == '#')
											{
												hashtag_counter++;
											}
											index++;
										}
										extended_tweet_length = strlen($3);
										sprintf($$,"%s %s %s%s", $1, $2, $3, $4);
									}
	;

extended_tweet_display_text_range : STRING double_dot extended_tweet_unsign_tuple comma
														{
															if(strcmp("\"display_text_range\"", $1) != 0)
															{
																fprintf(stderr,"Error in line: %d\nInvalid extended tweet display text range field.\n", yylineno);
																exit(1);
															}
															sprintf($$,"%s %s %s%s", $1, $2, $3, $4);
														}
	;

extended_tweet_unsign_tuple : left_bracket UNSIGN comma UNSIGN right_bracket 
												{ 
												
													if(($2 != 0) || ($4 != extended_tweet_length))
													{
														fprintf(stderr,"Error in line: %d\nInvalid extended tweet display text range tuple field.\n", yylineno);
														exit(1);
													}
													char tuple[9];
													sprintf(tuple,"%s%d%s%d%s", $1, $2, $3, $4, $5);
													$$ = strdup(tuple);
												}  
	;

entities: entities_field 
				{
					if(hashtag_counter == 0)
					{
						fprintf(stderr,"Error in line: %d\nInvalid extended tweet hashtags field.\n", yylineno);
						exit(1);
					}
					sprintf($$,"%s", $1);
				}
		|
				{
					if(hashtag_counter > 0)
					{
						fprintf(stderr,"Error in line: %d\nMissing extended tweet hashtags field.\n", yylineno);
						exit(1);
					}
				}
	;

entities_field : STRING double_dot left_curly_bracket hashtags right_curly_bracket
												{
													if(strcmp("\"entities\"", $1) != 0)
													{
														fprintf(stderr,"Error in line: %d\nInvalid extended tweet entities field.\n", yylineno);
														exit(1);
													}
													sprintf($$,"%s %s\n%s%s%s", $1, $2, $3, $4, $5);
												}
	;

hashtags : STRING double_dot left_bracket indice_array right_bracket
												{
													if(hashtag_counter > hashtag_parsed)
													{
														fprintf(stderr,"Error in line: %d\nMissing extended tweet hashtag.\n", yylineno);
														exit(1);
													}
													if(hashtag_counter < hashtag_parsed)
													{
														fprintf(stderr,"Error in line: %d\nInvalid extended tweet hashtag.\n", yylineno);
														exit(1);
													}
													if(strcmp("\"hashtags\"", $1) != 0)
													{
														fprintf(stderr,"Error in line: %d\nInvalid extended tweet hashtags field.\n", yylineno);
														exit(1);
													}
													sprintf($$,"%s %s\n%s\n%s\n%s", $1, $2, $3, $4, $5);
												}
	;

indice_array : indice	{	$$ = strdup($1); }
			| indice comma indice_array	
			{
				char* text;
				text = strdup($3);
				sprintf($$,"%s%s\n%s", $1, $2, text);
			}
	;

indice : left_curly_bracket indice_text_field indice_tuple right_curly_bracket
									{
										char* hashtag_text = (char*)malloc(sizeof(char) * (strlen(indice_text) + 1));
										strcat(hashtag_text, "#");
										indice_text[strlen(indice_text) - 1] = 0;
										strcat(hashtag_text, &indice_text[1]);
										char* hashtag_pointer = strstr(full_text, hashtag_text);
										if(hashtag_pointer == NULL)
										{
											fprintf(stderr,"Error in line: %d\nInvalid extended tweet indice field.\n", yylineno);
											exit(1);
										}
										int position = (int)(hashtag_pointer - full_text);
										if((indice_tuple_start != position) || (indice_tuple_end != (strlen(hashtag_text) + position)))
										{
											fprintf(stderr,"Error in line: %d\nInvalid extended tweet indice field.\n", yylineno);
											exit(1);
										}
										char* text = (char*)malloc(sizeof(char) * (strlen($1) + strlen($2) + strlen($3) + strlen($4)));	
										sprintf(text,"%s%s\n%s%s", $1, $2, $3, $4);
										$$ = strdup(text);
										hashtag_parsed++;
									}
	;

indice_text_field :	STRING double_dot STRING comma
								{ 
									if(strcmp("\"text\"",$1) != 0)
									{
										fprintf(stderr,"Error in line: %d\nInvalid extended tweet text field.\n", yylineno);
										exit(1);
									}
									if((strlen($3)>140))
									{
										fprintf(stderr,"Error in line: %d\nExtended tweet text field must have maximum 140 characters.\n", yylineno);
										exit(1);
									}
									indice_text = strdup($3);
									sprintf($$, "%s %s %s%s", $1, $2, $3, $4);
								}
	;
indice_tuple : STRING double_dot left_bracket UNSIGN comma UNSIGN right_bracket
										{
											if(strcmp("\"indices\"", $1) != 0)
											{
												fprintf(stderr,"Error in line: %d\nInvalid extended tweet indice tuple field.\n", yylineno);
												exit(1);
											}
											char tuple[9];
											indice_tuple_start = $4;
											indice_tuple_end = $6;
											sprintf(tuple,"%s%d%s%d%s", $3, $4, $5, $6, $7);
											sprintf($$,"%s %s %s", $1, $2, tuple);
										}
	;

tweet_object: left_curly_bracket tweet_created_at_field tweet_id_string_field tweet_text_field tweet_user_field right_curly_bracket
																			{
																				char* printf_string;
																				asprintf(&printf_string,"%s\n%s\n%s\n%s\n%s\n%s", $1, $2, $3, $4, $5, $6);
																				int left_bracket_counter = 0;
																				int right_bracket_counter = 0;
																				for(int i = 0; i < strlen(printf_string); i++)
																				{
																					if(printf_string[i] == '{')
																					{
																						left_bracket_counter++;
																					}
																					if(printf_string[i] == '}')
																					{
																						right_bracket_counter++;
																					}
																					printf("%c",printf_string[i]);
																					if(printf_string[i] == '\n')
																					{
																						int j;
																						if(i+1 < strlen(printf_string) && printf_string[i+1] == '}')
																						{
																							for(j = 0; j < left_bracket_counter - right_bracket_counter - 1; j++)
																							{
																								printf("\t");
																							}
																						}
																						else
																						{
																							for(j = 0; j < left_bracket_counter - right_bracket_counter; j++)
																							{
																								printf("\t");
																							}
																						}
																					}
																				}
																			}
	;

retweet_object : left_curly_bracket retweeted_status_object comma retweeted_tweet_object right_curly_bracket
																			{
																				char* printf_string;
																				asprintf(&printf_string,"%s%s%s%s%s", $1, $2, $3, $4, $5);
																				int left_bracket_counter = 0;
																				int right_bracket_counter = 0;
																				for(int i = 0; i < strlen(printf_string); i++)
																				{
																					if(printf_string[i] == '{')
																					{
																						left_bracket_counter++;
																					}
																					if(printf_string[i] == '}')
																					{
																						right_bracket_counter++;
																					}
																					printf("%c",printf_string[i]);
																					if(printf_string[i] == '\n')
																					{
																						int j;
																						if(i+1 < strlen(printf_string) && printf_string[i+1] == '}')
																						{
																							for(j = 0; j < left_bracket_counter - right_bracket_counter - 1; j++)
																							{
																								printf("\t");
																							}
																						}
																						else
																						{
																							for(j = 0; j < left_bracket_counter - right_bracket_counter; j++)
																							{
																								printf("\t");
																							}
																						}
																					}																				
																				}
																			}
	;
	
retweeted_tweet_object : STRING double_dot left_curly_bracket retweeted_tweet_text_field retweeted_tweet_user_field right_curly_bracket
	{
		if(strcmp("\"tweet\"",$1) != 0)
		{
			fprintf(stderr,"Error in line: %d\nInvalid retweet field.\n", yylineno);
			exit(1);
		}
		sprintf($$,"%s %s\n%s\n%s\n%s\n%s", $1, $2, $3, $4, $5, $6);	
	}
	;

retweeted_tweet_text_field : STRING double_dot STRING
									{
										char* retweeted_text = (char*)malloc(sizeof(char) * (strlen(retweeted_tweet_name) + strlen(retweeted_tweet_text) + 8));
										strcat(retweeted_text, "\"RT @");
										retweeted_tweet_name[strlen(retweeted_tweet_name) - 1] = ' ';
										strcat(retweeted_text, &retweeted_tweet_name[1]);
										retweeted_tweet_text[strlen(retweeted_tweet_text) - 1] = 0;
										strcat(retweeted_text, &retweeted_tweet_text[1]);
										strcat(retweeted_text, "\"");
										if((strcmp("\"text\"",$1) != 0) || (strlen($3)>140) || (strcmp(retweeted_text,$3) != 0))
										{
											fprintf(stderr,"Error in line: %d\nInvalid retweet text field.\n", yylineno);
											exit(1);
										}
										sprintf($$, "%s %s %s", $1, $2, $3);
									}
	;

retweeted_tweet_user_field : STRING double_dot left_curly_bracket retweet_user_screen_name_field right_curly_bracket
	{
		if(strcmp("\"user\"",$1) != 0)
		{
			fprintf(stderr,"Error in line: %d\nInvalid retweet user field.\n", yylineno);
			exit(1);
		}
		sprintf($$, "%s %s\n%s%s%s", $1, $2, $3, $4, $5);
	}
	;
	
retweet_user_screen_name_field : STRING double_dot STRING
												{
													if(strcmp("\"screen_name\"", $1) != 0)
													{
														fprintf(stderr,"Error in line: %d\nInvalid retweet screen name field.\n", yylineno);
														exit(1);
													}
													sprintf($$, "%s %s %s", $1, $2, $3);
												}
	;

retweeted_status_object : STRING double_dot left_curly_bracket retweeted_status_text_field retweeted_status_user_field right_curly_bracket
	{
		if(strcmp("\"retweeted_status\"",$1) != 0)
		{
			fprintf(stderr,"Error in line: %d\nInvalid retweet status field.\n", yylineno);
			exit(1);
		}
		sprintf($$, "%s %s\n%s%s%s%s\n", $1, $2, $3, $4, $5, $6);
	}
	;

retweeted_status_text_field : STRING double_dot STRING
									{
										printf("\n");
										if((strcmp("\"text\"",$1) != 0) || (strlen($3)>140))
										{
											fprintf(stderr,"Error in line: %d\nInvalid retweet status text field.\n", yylineno);
											exit(1);
										}
										retweeted_tweet_text = strdup($3);
										sprintf($$, "%s %s %s\n", $1, $2, $3);
									}
	;
	
retweeted_status_user_field : STRING double_dot left_curly_bracket retweeted_status_screen_name_field right_curly_bracket
	{
		if(strcmp("\"user\"",$1) != 0)
		{
			fprintf(stderr,"Error in line: %d\nInvalid retweet status user field.\n", yylineno);
			exit(1);
		}
		sprintf($$, "%s %s\n%s%s%s", $1, $2, $3, $4, $5);
	}
	;

retweeted_status_screen_name_field : STRING double_dot STRING
												{
													if(strcmp("\"screen_name\"", $1) != 0)
													{
														fprintf(stderr,"Error in line: %d\nInvalid retweet status screen name field.\n", yylineno);
														exit(1);
													}
													retweeted_tweet_name = strdup($3);
													sprintf($$, "%s %s %s", $1, $2, $3);
												}
	;

tweet_text_field :	STRING double_dot STRING comma
								{ 
									if((strcmp("\"text\"",$1) == 0) && (strlen($3)>=140))
									{
										fprintf(stderr,"Error in line: %d\nInvalid tweet text field.\n", yylineno);
										exit(1);
									}
									sprintf($$, "%s %s %s%s", $1, $2, $3, $4);
								}
	;	

tweet_created_at_field :	STRING double_dot STRING comma
								{ 
									if(strcmp("\"created_at\"",$1) == 0)
									{
										split_string = strdup($3);
										char* token = strtok(split_string, " "); 
										int index = 0;
										int flag = 0;
										while (token != NULL && index < 6) 
										{ 
											switch(index)
											{
												case 0: 
												for (counter = 0; counter < 7; counter++) 
												{ 														
													if(strcmp(days[counter], &token[1]) == 0)
													{
														flag = 1;
														break;
													}
												}
												if(flag == 0)
												{
													fprintf(stderr,"Error in line: %d\nInvalid tweet created at field.\n", yylineno);
													exit(1);
												}													
												break;
												case 1: 
												flag = 0;
												for (counter = 0; counter < 12; counter++) 
												{ 														
													if(strcmp(months[counter], token) == 0)
													{
														flag = 1;
														break;
													}
												}
												if(flag == 0)
												{
													fprintf(stderr,"Error in line: %d\nInvalid tweet created at field.\n", yylineno);
													exit(1);
												}													
												break;
												case 2: 
												{
													int day = atoi(token);
													if(day < 1 || day > 32)
													{
														fprintf(stderr,"Error in line: %d\nInvalid tweet created at field.\n", yylineno);
														exit(1);
													}
												}
												break;
												case 3: 
												{
													int time_counter = 0;
													int time_value;
													char* timestamp;
													char* timestamp_token;
													timestamp = strdup(token);
													timestamp_token = strtok(timestamp, ":");												
													while (timestamp_token != NULL && time_counter < 3) 
													{
														time_value = atoi(timestamp_token);
														if (time_counter == 0 )
														{
															if(time_value < 0 || time_value > 24)
															{
																fprintf(stderr,"Error in line: %d\nInvalid tweet created at field.\n", yylineno);
																exit(1);
															}
														}
														if(time_counter == 1)
														{
															if(time_value < 0 || time_value > 59)
															{
																fprintf(stderr,"Error in line: %d\nInvalid tweet created at field.\n", yylineno);
																exit(1);
															}
														}
														if(time_counter == 2)
														{	
															if(time_value < 0 || time_value > 59)
															{
																fprintf(stderr,"Error in line: %d\nInvalid tweet created at field.\n", yylineno);
																exit(1);
															}
														}
														timestamp_token = strtok(NULL, ":");
														time_counter++;
													}
												}
												break;
												case 4: 
												{
													int timezone = atoi(token);
													if(timezone < -13 || timezone > 13)
													{
														fprintf(stderr,"Error in line: %d\nInvalid tweet created at field.\n", yylineno);
														exit(1);
													}
												}
												break;
												case 5: 
												{
													token[4] = ' ';
													int year = atoi(token);
													if(year < 1900)
													{
														fprintf(stderr,"Error in line: %d\nInvalid tweet created at field.\n", yylineno);
														exit(1);
													}
												}
												break;
											}
											token = strtok(NULL, " ");
											index++;
										}
										sprintf($$,"%s %s %s%s", $1, $2, $3, $4);
									}
								}
	;

tweet_user_field : STRING double_dot left_curly_bracket user_attributes right_curly_bracket 
								{ 
									if(strcmp("\"user\"",$1) != 0)
									{
										fprintf(stderr,"Error in line: %d\nInvalid tweet user field.\n", yylineno);
										exit(1);
									}
									sprintf($$,"%s %s\n%s%s%s", $1, $2, $3, $4, $5);
								}
	;
	
user_attributes : user_id_field  user_name_field  user_screen_name_field  user_location_field  
										{
											sprintf($$,"%s\n%s\n%s\n%s", $1, $2, $3, $4);
										}
	;
	
user_id_field : STRING double_dot UNSIGN comma
											{																								
												if(strcmp("\"id\"", $1) == 0)
												{												
													for(counter = 0; counter < tweet_id_array_size; counter++)
													{
														if(tweet_id[counter] == $3)
														{
															fprintf(stderr,"Error in line: %d\nDuplicate user id: %d.\n", yylineno, tweet_id[counter]);
															exit(1);
														}
													}
													if(tweet_id_array_size == tweet_id_array_max_size)
													{
														tweet_id_array_max_size = tweet_id_array_max_size + 10;
														tweet_id = (int*)realloc(tweet_id, sizeof(int)*tweet_id_array_max_size);
														tweet_id[tweet_id_array_size] = $3;
														tweet_id_array_size++;
													}
													else
													{
														tweet_id[tweet_id_array_size] = $3;
														tweet_id_array_size++;
													}
													sprintf($$,"%s %s %d%s", $1, $2, $3, $4);
												}
											}
	;

user_name_field : STRING double_dot STRING comma
												{
													if(strcmp("\"name\"", $1) != 0)
													{
														fprintf(stderr,"Error in line: %d\nInvalid tweet name field.\n", yylineno);
														exit(1);
													}
													sprintf($$,"%s %s %s%s", $1, $2, $3, $4);
												}
	;

user_screen_name_field : STRING double_dot STRING comma
												{
													if(strcmp("\"screen_name\"", $1) != 0)
													{
														fprintf(stderr,"Error in line: %d\nInvalid tweet screen name field.\n", yylineno);
														exit(1);
													}
													sprintf($$, "%s %s %s%s", $1, $2, $3,$4);
												}
	;
	
user_location_field  : STRING double_dot STRING comma
												{
													if(strcmp("\"location\"", $1) != 0)
													{
														fprintf(stderr,"Error in line: %d\nInvalid tweet location field.\n", yylineno);
														exit(1);
													}
													sprintf($$,"%s %s %s%s", $1, $2, $3, $4);
												}
	;

tweet_id_string_field : STRING double_dot STRING comma
													{
														if(strcmp("\"id_str\"", $1) == 0)
														{
															input_string = strdup($3);
															id_string = strtoll(&input_string[1],NULL,10);
															if(id_string < 0)
															{
																fprintf(stderr,"Error in line: %d\nNegative id string.\n", yylineno);
																exit(1);
															}
															for(counter = 0; counter < tweet_id_string_array_size; counter++)
															{
																if(tweet_id_string[counter] == id_string)
																{
																	fprintf(stderr,"Error in line: %d\nDuplicate id string: %d.\n", yylineno, tweet_id[counter]);
																	exit(1);
																}
															}
															if(tweet_id_string_array_size == tweet_id_string_array_max_size)
															{
																tweet_id_string_array_max_size = tweet_id_string_array_max_size + 10;
																tweet_id_string = (long long int *)realloc(tweet_id_string, sizeof(long long int) * tweet_id_string_array_max_size);
																tweet_id_string[tweet_id_string_array_size] = id_string;
																tweet_id_string_array_size++;
															}
															else
															{
																tweet_id_string[tweet_id_string_array_size] = id_string;
																tweet_id_string_array_size++;
															}
															sprintf($$,"%s %s %s%s", $1, $2, $3, $4);
														}
													}
	;
	
number	: SIGN { asprintf(&$$,"%d", $1); }
		| UNSIGN { asprintf(&$$,"%d", $1); }
		| REAL { asprintf(&$$,"%g", $1); }
		| scientific { sprintf($$,"%s", $1); }
	;

scientific	: SIGN epsilon SIGN	{ asprintf(&$$,"%d%s%+d", $1, $2, $3); }
			| UNSIGN epsilon SIGN { asprintf(&$$,"%d%s%+d", $1, $2, $3); }
			| REAL epsilon SIGN	{ asprintf(&$$,"%g%s%+d", $1, $2, $3); }	
	;	
%%

void yyerror(char const *s) 
{
    fprintf(stderr,"\nError: %s\nLine: %d\nToken: %s\n", s, yylineno, yytext);
	exit(1);
}									


int main ( int argc, char **argv  ) 
{
	tweet_id = (int*)malloc(sizeof(int) * tweet_id_array_max_size);
	tweet_id_string = (long long int*)malloc(sizeof(long long int) * tweet_id_string_array_max_size);
	++argv; --argc;
	if ( argc > 0 )
		yyin = fopen( argv[0], "r" );
	else
		yyin = stdin;
	yyparse ();
	fprintf(stderr, "%s", "\n\nParsing was completed successfully\n");
	return 0;
}   