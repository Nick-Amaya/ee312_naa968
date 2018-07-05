
#include <stdio.h>
#include <string.h>

/* For use in delimiting the beginning and end of functions */
#define BEGIN_FCN {
#define END_FCN		}
#define N					20
#define M					20
#define STR_LEN		200

void locate_functions(char output_array[N][STR_LEN], FILE * fp)
BEGIN_FCN

	int l = 0;
	int fcn_number = 0;
	int line_index;
	int in_word;
	int word_count = 0;
	char temp[STR_LEN];
	char line[STR_LEN];
	char prev_line[STR_LEN];

	fgets(prev_line, STR_LEN, fp);
	while(fgets(line, STR_LEN, fp) != NULL) {
		if(strcmp(line, "BEGIN_FCN\n") == 0) {

			line_index = 0;
			in_word = 0;
			l = 0;
			word_count = 0;

			while(prev_line[line_index] != '(') {
				switch(prev_line[line_index]) {

					case ' ': case '\t': case '\0': case '\n': case '\r':
						if(in_word == 1) {
							in_word = 0;
						}
						break;

					default:
						if(in_word == 0) {
							word_count++;
						}
						if(word_count == 2) {
							output_array[fcn_number][l] = prev_line[line_index];
							l++;
						}
						in_word = 1;
						break;
				}
				line_index++;
			}
			fcn_number++;
		}
		strcpy(prev_line, line);
	}

END_FCN

int fcount(int output[M], FILE * fp)
BEGIN_FCN

	//flags
	int within_comments = 0;
	int within_quotations = 0;
	int within_singlequotes = 0;
	int within_function = 0;
	int singleline_comment = 0;

	char line[STR_LEN];
	int line_index;
	int fcn_index = 0;
	int file_index = 1;

	while(fgets(line, STR_LEN, fp) != NULL) {

		if(strcmp(line, "BEGIN_FCN\n") == 0) {
			if(within_function == 0) {
				within_function = 1;
			} else {
				return -1;
			}
		}

		if(strcmp(line, "END_FCN\n") == 0) {
			if(within_function == 1) {
				within_function = 0;
				fcn_index++;
			} else {
				return -1;
			}
		}

		if(singleline_comment == 1) {
			singleline_comment = 0;
			within_comments = 0;
		}

		if(within_function) {
			//printf("line[%d]: ", file_index);
			line_index = 0;
			while(line_index < STR_LEN && line[line_index] != '\n') {
				//printf("%c", line[line_index]);
				switch(line[line_index]) {
					case ';':
						if(within_comments == 0 && within_quotations == 0 && within_singlequotes == 0) {
							output[fcn_index]++;
							//printf("output[%d]: %d\t\t\tline[%d]: %s", fcn_index, output[fcn_index], file_index, line);
						}
						break;

					case '"':
						if(within_singlequotes == 0 && within_comments == 0) {
							if(within_quotations == 0) {
								within_quotations = 1;
							} else {
								within_quotations = 0;
							}
						}
						break;

					case '\'':
						if(within_quotations == 0 && within_comments == 0) {
							if(within_singlequotes == 0) {
								within_singlequotes = 1;
							} else {
								within_singlequotes = 0;
							}
						}
						break;

					case '/':
						if(within_quotations == 0 && within_comments == 0 && within_singlequotes == 0) {
							if(line[line_index + 1] == '/') {
								within_comments = 1;
								singleline_comment = 1;
							}
							if(line[line_index + 1] == '*') {
								within_comments = 1;
								singleline_comment = 0;
							}
						}
						break;

					case '*':
						if(within_comments == 1 && line[line_index + 1] == '/') {
							within_comments = 0;
						}
						break;

					case '\\':
						if(within_quotations == 1 || within_singlequotes == 1) {
							line_index++;
						}
						break;

					default:
						break;
				}
				line_index++;
			}
		}
		file_index++;
		//printf("\n");
	}

	if(within_function) {
		return -1;
	}

	return 0;
END_FCN


int main(void)
BEGIN_FCN
	FILE * user_file;
	FILE * output_file;
	char user_fileinput[STR_LEN];
	char user_fileoutput[STR_LEN];

	//output data
	char fcn_names[N][STR_LEN];
	int number_of_statements[M];
	int total_fcns;
	int total_linesofcode;

	//instruct the user on how to use the program
	printf("Enter file name to count size of. Enter 'STOP' to quit the program.\n");

	do {

		//clear output arrays
		for(int j = 0; j < M; j++) {
			number_of_statements[j] = 0;
		}
		for(int j = 0; j < N; j++) {
			strcpy(fcn_names[j], "");
		}

		//*** Open up user inputted file ***
		printf(": ");
		scanf("%s", user_fileinput);

		user_file = fopen(user_fileinput, "r");
		if(user_file == NULL) {
			if(strcmp("STOP", user_fileinput) != 0) {
				printf("\tNo such file exists. \n");
			}

			fclose(user_file);
			continue;
		}

		//check output file
		printf("\nEnter file name to write data to: ");
		scanf("%s", user_fileoutput);
		output_file = fopen(user_fileoutput, "w");
		if(output_file == NULL) {
			fclose(output_file);
			continue;
		}

		//*** populate my output data arrays ***
		//initialize data arrays
		if(fcount(number_of_statements, user_file) == -1) {
			printf("\nError: Functions are not properly aligned.\n\n");
			continue;
		}
		rewind(user_file);
		locate_functions(fcn_names, user_file);


		//calculate total number of functions and total lines of code
		total_fcns = 0;
		total_linesofcode = 0;
		while(number_of_statements[total_fcns] != 0) {
			total_linesofcode += number_of_statements[total_fcns];
			total_fcns++;
		}

		if(total_fcns == 0) {
			printf("\nError: No functions were found.\n\n");
			continue;
		}

		//print output data to the screen
		printf("\nFile Counting Summary Table\n\nFilename: %s\n\n", user_fileinput);
		printf("Function Name\t\t# Lines of Code\n\n");

		for(int j = 0; j < total_fcns; j++) {
			printf("%s\t\t\t%d\n", fcn_names[j], number_of_statements[j]);
		}

		printf("\nTotal Functions: %d\nTotal Lines of Code: %d\n\n", total_fcns, total_linesofcode);

		//write output data to another file specified by the user
		fprintf(output_file, "\nFile Counting Summary Table\n\nFilename: %s\n\n", user_fileinput);
		fprintf(output_file, "Function Name\t\t# Lines of Code\n\n");

		for(int j = 0; j < total_fcns; j++) {
			fprintf(output_file, "%s\t\t\t%d\n", fcn_names[j], number_of_statements[j]);
		}

		fprintf(output_file, "\nTotal Functions: %d\nTotal Lines of Code: %d\n\n", total_fcns, total_linesofcode);

		//close file
		fclose(output_file);
		fclose(user_file);

	} while(strcmp("STOP", user_fileinput) != 0);
	/* The sentinel is the keyword "STOP" */
END_FCN
