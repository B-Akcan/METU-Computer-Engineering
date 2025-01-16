#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "parser.h"

void handle_command_seq(single_input inp);
void handle_command_para(single_input inp);
void handle_separator_seq(parsed_input input);
void handle_separator_para(parsed_input input);
void handle_separator_pipe(parsed_input input);
void handle_subshell(single_input inp);

int main()
{
	char *str = NULL;
	size_t input_size = INPUT_BUFFER_SIZE;
	parsed_input input;

	printf("/> ");
	getline(&str, &input_size, stdin);

	while (strcmp(str, "quit\n"))
	{
		if (parse_line(str, &input))
		{
			//pretty_print(&input);

			switch (input.separator)
			{
				case SEPARATOR_NONE:
				{
					single_input inp = input.inputs[0];

					switch (inp.type)
					{
						case INPUT_TYPE_COMMAND:
						{
							handle_command_seq(inp);
							break;
						}

						case INPUT_TYPE_SUBSHELL:
						{
							int child_status;
							
							pid_t pid = fork();
							if (pid == 0) // child process
								handle_subshell(inp);
							else // parent process
								wait(&child_status);
								
							break;
						}
					}
					
					break;
				}

				case SEPARATOR_PIPE:
				{
					handle_separator_pipe(input);
					break;
				}

				case SEPARATOR_SEQ:
				{
					handle_separator_seq(input);
					break;
				}

				case SEPARATOR_PARA:
				{
					handle_separator_para(input);
					break;
				}
			}
		}

		printf("/> ");

		free_parsed_input(&input);
		getline(&str, &input_size, stdin);
	}

	return 0;
}

void handle_command_seq(single_input inp)
{
	int child_status;

	pid_t pid = fork();
	if (pid == 0) // child process
	{
		execvp(inp.data.cmd.args[0], inp.data.cmd.args);
		exit(0);
	}
	else // parent process
	{
		wait(&child_status);
	}
}

void handle_command_para(single_input inp)
{
	pid_t pid = fork();
	if (pid == 0) // child process
	{
		execvp(inp.data.cmd.args[0], inp.data.cmd.args);
		exit(0);
	}
}

void handle_separator_seq(parsed_input input)
{
	int n_inputs = input.num_inputs;
	int child_status;

	for (int i=0; i<n_inputs; i++)
	{
		single_input inp = input.inputs[i];

		switch (inp.type)
		{
			case INPUT_TYPE_COMMAND:
			{
				handle_command_seq(inp);
				break;
			}
			
			case INPUT_TYPE_PIPELINE:
			{
				pipeline pipeln = inp.data.pline;
				int n_inputs_pipeline = pipeln.num_commands;
				int pipefds[n_inputs_pipeline - 1][2];

				for (int j=0; j<n_inputs_pipeline; j++)
				{
					if (j < n_inputs_pipeline - 1)
						pipe(pipefds[j]);

					pid_t pid = fork();
					if (pid == 0) // child process
					{
						if (j == 0) // 1st process
						{
							// write to next pipe
							dup2(pipefds[j][1], 1);
							
							// close the pipe
							close(pipefds[j][0]);
							close(pipefds[j][1]);
						}
						else if (j > 0 && j < n_inputs_pipeline - 1) // middle process
						{
							// read from last pipe
							dup2(pipefds[j-1][0], 0);
							
							// write to next pipe
							dup2(pipefds[j][1], 1);

							// close all pipes
							for (int k=0; k <= j; k++)
							{
								close(pipefds[k][0]);
								close(pipefds[k][1]);
							}
						}
						else // last process
						{
							// read from last pipe
							dup2(pipefds[j-1][0], 0);

							// close all pipes
							for (int k=0; k < j; k++)
							{
								close(pipefds[k][0]);
								close(pipefds[k][1]);
							}
						}
						
						execvp(pipeln.commands[j].args[0], pipeln.commands[j].args);
						exit(0);
					}
				}

				for (int j=0; j < n_inputs_pipeline; j++) // parent process
				{
					if (j < n_inputs_pipeline - 1)
					{
						close(pipefds[j][0]);
						close(pipefds[j][1]);
					}
					
					wait(&child_status);
				}

				break;
			}
		}
	}
}

void handle_separator_para(parsed_input input)
{
	int n_inputs = input.num_inputs;
	int child_status;

	for (int i=0; i<n_inputs; i++)
	{
		single_input inp = input.inputs[i];

		switch (inp.type)
		{
			case INPUT_TYPE_COMMAND:
			{
				handle_command_para(inp);
				break;
			}

			case INPUT_TYPE_PIPELINE:
			{
				pipeline pipeln = inp.data.pline;
				int n_inputs_pipeline = pipeln.num_commands;
				int pipefds[n_inputs_pipeline - 1][2];

				for (int j=0; j<n_inputs_pipeline; j++)
				{
					if (j < n_inputs_pipeline - 1)
						pipe(pipefds[j]);

					pid_t pid = fork();
					if (pid == 0) // child process
					{
						if (j == 0) // 1st process
						{
							// write to next pipe
							dup2(pipefds[j][1], 1);
							
							// close the pipe
							close(pipefds[j][0]);
							close(pipefds[j][1]);
						}
						else if (j > 0 && j < n_inputs_pipeline - 1) // middle process
						{
							// read from last pipe
							dup2(pipefds[j-1][0], 0);
							
							// write to next pipe
							dup2(pipefds[j][1], 1);

							// close all pipes
							for (int k=0; k <= j; k++)
							{
								close(pipefds[k][0]);
								close(pipefds[k][1]);
							}
						}
						else // last process
						{
							// read from last pipe
							dup2(pipefds[j-1][0], 0);

							// close all pipes
							for (int k=0; k < j; k++)
							{
								close(pipefds[k][0]);
								close(pipefds[k][1]);
							}
						}
						
						execvp(pipeln.commands[j].args[0], pipeln.commands[j].args);
						exit(0);
					}
				}

				for (int j=0; j < n_inputs_pipeline; j++) // parent process
				{
					if (j < n_inputs_pipeline - 1)
					{
						close(pipefds[j][0]);
						close(pipefds[j][1]);
					}
					
					wait(&child_status);
				}

				break;
			}
		}
	}

	for (int i=0; i < n_inputs; i++)
	{
		wait(&child_status);
	}
}

void handle_separator_pipe(parsed_input input)
{
	int child_status;
	int n_inputs = input.num_inputs;
	int pipefds[n_inputs - 1][2];

	for (int i=0; i<n_inputs; i++)
	{
		single_input inp = input.inputs[i];

		if (i < n_inputs - 1)
			pipe(pipefds[i]);

		pid_t pid = fork();
		if (pid == 0) // child process
		{
			if (i == 0) // 1st process or subshell
			{
				// write to next pipe
				dup2(pipefds[i][1], 1);
				
				// close the pipe
				close(pipefds[i][0]);
				close(pipefds[i][1]);
			}
			else if (i > 0 && i < n_inputs - 1) // middle process or subshell
			{
				// read from last pipe
				dup2(pipefds[i-1][0], 0);
				
				// write to next pipe
				dup2(pipefds[i][1], 1);
				
				// close pipes
				for (int j=0; j<=i; j++)
				{
					close(pipefds[j][0]);
					close(pipefds[j][1]);
				}
			}
			else // last process or subshell
			{
				// read from last pipe
				dup2(pipefds[i-1][0], 0);
				
				// close pipes
				for (int j=0; j<i; j++)
				{
					close(pipefds[j][0]);
					close(pipefds[j][1]);
				}
			}
			
			switch (inp.type)
			{
				case INPUT_TYPE_COMMAND:
				{
					execvp(inp.data.cmd.args[0], inp.data.cmd.args);
					exit(0);
					break;
				}
				
				case INPUT_TYPE_SUBSHELL:
				{
					handle_subshell(inp);
					break;
				}
			}
		}
	}

	for (int i=0; i < n_inputs; i++) // parent process
	{
		if (i < n_inputs - 1)
		{
			close(pipefds[i][0]);
			close(pipefds[i][1]);
		}
		
		wait(&child_status);
	}
}

void handle_subshell(single_input inp)
{
	parsed_input ss_input;

	if (parse_line(inp.data.subshell, &ss_input))
	{
		switch (ss_input.separator)
		{
			case SEPARATOR_NONE:
			{
				handle_command_seq(ss_input.inputs[0]);
				break;
			}
			
			case SEPARATOR_PIPE:
			{
				handle_separator_pipe(ss_input);
				break;
			}
			
			case SEPARATOR_SEQ:
			{
				handle_separator_seq(ss_input);
				break;
			}
			
			case SEPARATOR_PARA:
			{
				handle_separator_para(ss_input);
				break;
			}
		}
	}
	
	free_parsed_input(&ss_input);
}


