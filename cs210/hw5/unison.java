import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.*;

class unison {
	public static void main(String[] args) throws IOException {

		File file = new File("uniuml.json");	//This creates a new file or uses the existing file

		//This for loop loops through all of the files given in the command line
		for(String str : args) {

			//These two operations allow the user to 'write' to the given file
			FileWriter writer = new FileWriter(file, true);
			PrintWriter output = new PrintWriter(writer);

			File newFile = new File (str); //This implements the file to a 'try' or 'catch'
			try //If the file exists, conitnue
			{
				Scanner scanner = new Scanner(newFile); //This creates a scnnaer to read in the file
				int method = 0; //This acts as a boolean variable to test if a string is a method
				int classCheck = 0; //This acts as a boolean variable to test if a string is a class
				int fields = 0; //This acts as a boolean variable to test if a string contains fields

				//This while loop scans through every line of the newFile
				while (scanner.hasNextLine()) {
					String line = scanner.nextLine(); //This reads the line into a string
					boolean nonCommand = false; //This is a test to make sure the string is a command (i.e. not a comment)
					int length = line.length(); //This determines the length of the line
					List<Integer> superIndex = new ArrayList<>(); //This will contain all the supers in a class command
					List<Integer> fieldIndex = new ArrayList<>(); //This will contain all of the fields given in the command
					List<Integer> fieldEndIndex = new ArrayList<>(); //This determine the end of the field list
					List<Integer> listIndex = new ArrayList<>(); //This will contain all of the items in a given field
					int classIndex = 0; //This will be the index of the arrays above
					int index; //This will be the index of the string provided to manipulate
					int start = 0; //This will determine where the command actually starts (avoids white space)

					//This process increases the index of the string to avoid any white space
					if (start != length) {
						while(line.charAt(start) == ' ' || line.charAt(start) == '\t') {
							start++;
							if (start == length)
							{
								nonCommand = true;
								break;
							}
						}
					}
					//This for loop will read in the dirst command unless its a comment
					for(index = start; index < length; index++) {
						char aChar = line.charAt(index);
						if(aChar == '#') {
							nonCommand = true; //If it's a comment, it's not a command
						}
						if(aChar == ' ') {
							classIndex = index-start; //If the space after the initial command is found, break
							break;
						}
					}
					line = line.replaceAll("\\s", ""); //This removes all of the spaces from the command
					length = line.length(); //This determines the new length of the string
					//This for loop will determine if the command is a class, method, has supers, and/or has fields
					//It will add the command found to their respective arrays
					for(index = 0; index < length; index++) {
						char aChar = line.charAt(index);
						if(aChar == ':') {
							superIndex.add(index);
						}
						if(aChar == '(') {
							fieldIndex.add(index);
							listIndex.add(index);
						}
						if(aChar == ')') {
							fieldEndIndex.add(index);
						}
						if(aChar == ',') {
							listIndex.add(index);
						}
					}
					String function = line.substring(0,classIndex); //A new string is made from the actual command

					//This makes sure that the command is an actual command (i.e. a class or method)
					if(!function.equals("class") && !function.equals("method"))
					{
						nonCommand = true;
					}

					//This process will add any super classes if any are found
					if(!superIndex.isEmpty() && !nonCommand)
					{
						//If the command is a class, this will add super classes to it
						if(function.equals("class"))
						{
							if(classCheck == 0)
							{
								classCheck = 1;
							}
							else
							{
								if(method == 1)
								{
									output.println("");
									output.println("  }");
									output.println("}");
									method = 0;
								}
								else
								{
									output.println(" }");
								}
							}
						}
						String className = line.substring(classIndex,superIndex.get(0));
						output.println("{ \""+function+"\" : \""+className+"\",");
						output.print("  \"super\" : [");
						int size = superIndex.size();
						for(int i = 0; i < size; i++) {
							if(i == size-1)
							{
								String superName = line.substring(superIndex.get(i)+1,length);
								output.print("\""+superName+"\"]");
							}
							else
							{
								String superName = line.substring(superIndex.get(i)+1,superIndex.get(i+1));
								output.print("\""+superName+"\", ");
							}
						}
					}
					else if(!nonCommand) //If no super classes are found, continue without
					{
						if(function.equals("class"))
						{
							if(classCheck == 0)
							{
								classCheck = 1;
							}
							else
							{
								if(method == 1)
								{
									//These prints merely add another class if a class has already been listAdded
									//This does not make JSON-syntactical sense, it just prints out another Unicon file's class
									output.println("");
									output.println("  }");
									output.println("}");
									method = 0;
								}
								else
								{
									output.println(" }");
								}
							}
							if(fieldIndex.isEmpty()) //If there are no fields, end it
							{
								String className = line.substring(classIndex,length);
								output.print("{ \""+function+"\" : \""+className+"\"");
							}
							else //If there are, this add them
							{
								fields = 1;
								String className = line.substring(classIndex,fieldIndex.get(0));
								output.print("{ \""+function+"\" : \""+className+"\"");
								if(fieldIndex.get(0) != fieldEndIndex.get(0)-1) //If the list isn't empty, print this out
								{
									output.println(",");
									output.print("  \"fields\" : [");
								}
								int size = listIndex.size();
								for(int i = 0; i < size; i++) //For every field, it prints this out
								{
									if(fieldIndex.get(0) == fieldEndIndex.get(0)-1) 
									{
										//This makes sure it isn't at the end of the list. If so, print nothing
									}
									else if(i == size-1) //If this is the last field, print this
									{
										String fieldName = line.substring(listIndex.get(i)+1,fieldEndIndex.get(0));
										output.print("\""+fieldName+"\"]");
									}
									else //If it is not the last, print this
									{
										String fieldName = line.substring(listIndex.get(i)+1,listIndex.get(i+1));
										output.print("\""+fieldName+"\", ");
									}
								}
							}
						}
						else if(function.equals("method")) //Instead, if the function is a method, process the following
						{
							if(method == 0) //If this is the first method, print this
							{
								if(classCheck == 1) //If there is a class prior, print a comma (never really happens anyway)
									output.println(",");
								output.println("  \"methods\": {");
								method = 1;
							}
							else //If it is not the first, it print a comma for the itself
							{
								if(classCheck == 1)
									output.println(",");
							}
							//A new string is made from the actual method command
							String methodName = line.substring(classIndex,fieldIndex.get(0));
							output.print("    \""+methodName+"\": [");
							int size = listIndex.size();
							int listindex = 0; //This will acts as an 'listArray' index
							int first = 0; //This is a one time use variable use for the first list item in the field

							/*This entire process checks for in-line comments that may be conflicting with the end
							 *of a field. For example
							 *method example(item1, #comment
							 *item2,
							 *#comment
							 *item3)
							*/
							if(fieldEndIndex.isEmpty())
							{
								while(fieldEndIndex.isEmpty()) //It will continue reading down the line until it finds an end
								{
									nonCommand = false;
									int listAdded = 0;
									if(fieldIndex.get(0) != length-1 && first == 0) //if it finds fields on the way, this adds them
									{
										first = 1;
										for(int i = 0; i < size; i++)
										{
											if(i != size-1)
											{
												String fieldName = line.substring(listIndex.get(i)+1,listIndex.get(i+1));
												if(fieldName.charAt(0) != '#')
												{
													output.print("\""+fieldName+"\", ");
												}
											}
											else
											{
												if(listIndex.get(i) != length-1)
												{
													String fieldName = line.substring(listIndex.get(i)+1,length);
													if(fieldName.charAt(0) != '#')
													{
														output.print("\""+fieldName+"\", ");
													}
												}
											}
										}
									}
									String nextline = scanner.nextLine();
									length = nextline.length();
									start = 0;
									if (start != length)
									{
										while(nextline.charAt(start) == ' ' || nextline.charAt(start) == '\t') {
											start++;
											if (start == length)
											{
												nonCommand = true;
												break;
											}
										}
									}
									for(index = start; index < length; index++) {
										char aChar = nextline.charAt(index);
										if(aChar == '#') {
											nonCommand = true; //Weeds out comments
										}
										if(aChar == ' ') {
											listIndex.add(index-start);
											break;
										}
									}
									//This goes to the next line to find the end of the field list or more items in the field
									nextline = nextline.replaceAll("\\s", ""); 
									length = nextline.length();
									listIndex.add(-1);
									listindex = listIndex.size()-1;
									if(!nonCommand) //If it is a not a comment
									{
										for(index = 0; index < length; index++) {
											char aChar = nextline.charAt(index);
											if(aChar == ')') {
												fieldEndIndex.add(index);
											}
											if(aChar == ',') {
												listIndex.add(index);
												listAdded++;
												listindex++;
											}
										}
										if(fieldEndIndex.isEmpty())
										{
											if(listAdded > 0)
											{
												for(int i = listindex-listAdded; i < listindex; i++) {
													String fieldName = nextline.substring(listIndex.get(i)+1,listIndex.get(i+1));
													if(fieldName.charAt(0) != '#')
													{
														output.print("\""+fieldName+"\", ");
													}
												}
											}
										}
										else
										{
											if(listAdded > 0)
											{
												for(int i = listindex-listAdded; i <= listindex; i++) {
													if(i == listindex)
													{
														String fieldName = nextline.substring(listIndex.get(i)+1,fieldEndIndex.get(0));
														if(fieldName.charAt(0) != '#')
														{
															output.print("\""+fieldName+"\"]");
														}
													}
													else
													{
														String fieldName = nextline.substring(listIndex.get(i)+1,listIndex.get(i+1));
														if(fieldName.charAt(0) != '#')
														{
															output.print("\""+fieldName+"\", ");
														}
													}
												}
											}
											else
											{
												String fieldName = nextline.substring(listIndex.get(listindex)+1,fieldEndIndex.get(0));
												if(fieldName.charAt(0) != '#')
												{
													output.print("\""+fieldName+"\"]");
												}
											}
										}
									}
								}
							}
							else //When it does find the end, end the field list
							{
								for(int i = 0; i < size; i++) {
									if(fieldIndex.get(0) == fieldEndIndex.get(0)-1)
									{
										output.print("]");
									}
									else if(i == size-1)
									{
										String fieldName = line.substring(listIndex.get(i)+1,fieldEndIndex.get(0));
										output.print("\""+fieldName+"\"]");
									}
									else
									{
										String fieldName = line.substring(listIndex.get(i)+1,listIndex.get(i+1));
										output.print("\""+fieldName+"\", ");
									}
								}
							}
						}
					}
				}
				if(method == 1) //If there were methods, end with a brace
				{
					output.println("");
					output.println("  }");
					if(classCheck == 1)
						output.println("}"); //If there was a class, end with a brace
					method = 0;
				}
				else
				{
					if(classCheck == 1)
						output.println(" }"); //If there was a class, end with a brace
				}
				//These processes close the output and scanner
				output.close();
				scanner.close();
			}
			catch (FileNotFoundException ex) //If the file was not found, catch the error and end
			{
				output.println("No files found");
			}
		}
	}
}
