
int printTriangle(int size) {
  int starCount=0,i=1,j;  //start with starCount being 0

  while(i<=size)  //count from 0 (inclusive) to size (exclusive), for each number i that you count
    {  j=1;
      while(j<=i) //count from 0 (inclusive) to i (inclusive), for each number j that you count
	{
	  printf("*"); //print a "*"
	  j++;
	  starCount++; //increment starCount

	} //when you finish counting on j, 

      printf("\n");  //print a newline ("\n")
      i++;
    } //when you finish counting on i, 

  return starCount; //your answer is starCount

}


int main(void) {
  int numStars;
  printf("Here is a triangle with height 4\n");
  numStars = printTriangle(4);
  printf("That triangle had %d total stars\n", numStars);
  printf("Here is a triangle with height 7\n");  //now print "Here is a triangle with height 7\n"

  numStars = printTriangle(7); //then call printTriangle, passing in 7, and assign the result to numStars

  printf("That triangle had %d total stars\n",numStars);//finally, print "That triangle had %d total stars\n", such that the %d 
  //prints the value of numStars


  return 0;
}



