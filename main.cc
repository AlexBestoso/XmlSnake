#include <stdio.h>
#include <string>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <typeinfo>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlreader.h>

using namespace std;

#include "./xmlSnake.class.h"

int main(){
	/*
	 * example writing xml file.
	 * */
	XmlSnake xml;
	if(!xml.openFileWriter("./bananaTest")){
		printf("Failed to open\n");
		return 1;
	}
	if(!xml.startWritingFile()){
		printf("Failed to start writer.\n");
		return 1;
	}
	if(!xml.startWritingElement("root")){
		printf("Failed to start writing element.\n");
		return 1;
	}
	if(!xml.writeAttribute("encrypted", "false")){
		printf("Failed to add attribute to root element.\n");
		return 1;
	}
	if(!xml.writeComment("This comment is a test comment. Some may say that it's the greatest test comment.")){
		printf("Failed to comment on greatest test comment.\n");
		return 1;
	}

	if(!xml.writeElement("password", "secret_password")){
		printf("Failed to write full element.\n");
		return 1;
	}



	if(!xml.stopWritingElement()){
		printf("Failed to stop writing element.\n");
		return 1;
	}
	if(!xml.stopWritingFile()){
		printf("Faild to stop writer.\n");
		return 1;
	}
	xml.closeFileWriter();


	/*
	 * Example Reading XML file
	 * */
	if(!xml.openFileReader("./bananaTest")){
		printf("Failed to open file for read.\n");
		return 1;
	}

	while(xml.readLineReader()){
		printf("Name : %s\tValue : %s", xml.readResult.name.c_str(), xml.readResult.value.c_str());
		if(xml.readResult.attributeLen > 0){
			printf("\t");
			for(int i=0; i<xml.readResult.attributeLen; i++){
				printf("%s |", xml.readResult.attributes[i].c_str());
			}

			printf("\tFound Attribute 'encrypted' : %s", xml.getAttributeByName("encrypted").c_str());
		}

		printf("\n");
	}

	xml.closeReader();
	return 0;
}
