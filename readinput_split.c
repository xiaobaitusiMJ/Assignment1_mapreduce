#include"stdio.h"
#include <malloc.h>
#include"pthread.h"

#define nSplit 5

int flen;

char * readInput(char *filename)
{
	FILE *fIn;
	
	char *p;
		
	fIn = fopen(filename,"r");  // open the file 
	
	if(fIn == NULL){
	
		printf("open error\n");
		return 0;
	}

	fseek(fIn,0L,SEEK_END); /* 定位到文件末尾 */
	
	flen = ftell(fIn);  // get the length of the file

	//printf("flen = %d\n",flen);
	p = (char *)malloc(flen+1);  // create a region of memory to store the contents of the file

	if(p==NULL)
	{
		
		printf("malloc error\n");		
		fclose(fIn);
		return 0;
	} 
	
	fseek(fIn,0L,SEEK_SET); /* 定位到文件开头 */

	fread(p,sizeof(char),flen,fIn);  // load the data to memroy
	
	p[flen]=0;  // EOF? 
	
	
	
	fclose(fIn);
	
	return p;		

}

void split(char *p, char **pSplit,int Slen[])
{
	
	int i;
	int startPos=0;
	int endPos=0;

	int length;

	length = flen/nSplit;

	startPos=0;
        
	/* get the position of the first character which is a uppercase or lowercase letter*/
 
	while(!(('a' <= p[startPos] && p[startPos] <= 'z')||('A' <= p[startPos] && p[startPos]< 'Z'))){
	
			startPos++;
	}
	
	

	for(i=0;i<nSplit;i++){
	 
				
		
		pSplit[i] = &p[startPos];   //  place the start position of every split into a pointer array
		
		endPos = startPos + length;  // Note that this is not the exactly right end position          
		
		if(endPos<flen){
		
                        // make sure that the end postion of next split does not lie in the middle of one word
			while(('a' <= p[endPos] && p[endPos] <= 'z')||('A' <= p[endPos] && p[endPos]< 'Z')){
		
				endPos++;
			
			
			}
		
			Slen[i] = endPos-startPos; // the length of one split
			
			// get the start position of next split and make sure it starts from an english letter
			
			startPos=endPos+1;
			while((!(('a' <= p[startPos] && p[startPos] <= 'z')||('A' <= p[startPos] && p[startPos]< 'Z')))&&startPos<flen){
	
				startPos++;
			
			}			

		}else {
		
			Slen[i]=flen-startPos-1; // get the length of last split, note the end position is flen-1 
				
		}
	
	}
	
	

}

void map()
{
	


}

void main(int argc,char **argv)
{
	
	char *p;
	char *pSplit[nSplit];  // create a pointer array to store the start position of every split of the data
	
	int Slen[nSplit]={0};  // record the length of every split
	int i,j;

	if(argc!=2){
	
		printf("type the filename!\n");	
		return;
	}
	
	
	p = readInput(argv[1]);   //read the data
	
	split(p,pSplit,Slen);    // split the data to nSplit=5 parts
	
	//  show the result	
	for(i=0;i<nSplit;i++){
		
		printf("\n\n");
		for(j=0;j<Slen[i];j++){
			
			printf("%c",pSplit[i][j]);		
		}
	}
	

	
	
	

}
