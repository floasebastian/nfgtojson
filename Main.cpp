//precompiled header here:

//self defined header here:
#include "SimpleVertex.h"

//system header here:
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;
bool NFG2JSON(const char * filename);
int Vertex2JSON(Vertex vertex);

int main(int argc, char* argv[]){
	bool success = false;
	string filepath;
	if (argc > 1){
		filepath = string(argv[1]);
	}
	else{
		system("echo Please input the file address: ");
		cin >> filepath;
	}

	success = NFG2JSON(filepath.c_str());
	if (success){
		system("echo CONVERT_SUCCESS\n");
	}
	else{
		system("echo CONVERT_FAILED\n");
	}
	system("pause");
	return 0;
}



bool NFG2JSON(const char * filename){
	int nVertices = 0; 
	int nIndices = 0;
	string jsonFilename(filename);
	FILE * file = fopen(filename, "r");
	if (file != NULL){
		jsonFilename += ".json";
		ofstream json(jsonFilename);
		json << "{";
		fscanf(file, "%*s %d\n", &nVertices);

		json << "\"vertexDesc\": \"pos:vec3, norm:vec3, binorm:vec3, tgt:vec3, uv:vec2\",";

		json << "\"attribPos\": {\"pos\":" << 0 << ", \"norm\" : " << sizeof(Vector3) << ", \"binorm\":" << 2 * sizeof(Vector3); 
		json << ", \"tgt\":" << 3 * sizeof(Vector3) << ", \"uv\":" << 4 * sizeof(Vector3) << "},";
		
		json << "\"vertexSize\":" << sizeof(Vertex) << ",";
		json << "\"verticesCount\":" << nVertices << ",";
		
		json << "\"verticesData\":[";
		for (int i = 0; i < nVertices; i++){
			Vertex newV;
			
			fscanf(file, "%*s pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\n",
				&newV.pos.x, &newV.pos.y, &newV.pos.z,
				&newV.norm.x, &newV.norm.y, &newV.norm.z,
				&newV.binorm.x, &newV.binorm.y, &newV.binorm.z,
				&newV.tgt.x, &newV.tgt.y, &newV.tgt.z,
				&newV.uv.x, &newV.uv.y);
			/*color is for testing only
			switch the color START
			switch (i % 3){
			case 0:
				newV.col.x = 1.0f; newV.col.y = 0.0f; newV.col.z = 0.0f; newV.col.w = 1.0f;
				break;
			case 1:
				newV.col.x = 1.0f; newV.col.y = 1.0f; newV.col.z = 0.0f; newV.col.w = 1.0f;
				break;
			case 2:
				newV.col.x = 0.0f; newV.col.y = 0.0f; newV.col.z = 1.0f; newV.col.w = 1.0f;
				break;
			}
			/*switch the color END*/
			
			//write the vertex to file
			//json << "[";
			json << fixed << setprecision(6);
			json << newV.pos.x << "," << newV.pos.y << "," << newV.pos.z << ",";
			json << newV.norm.x << "," << newV.norm.y << "," << newV.norm.z << ",";
			json << newV.binorm.x << "," << newV.binorm.y << "," << newV.binorm.z << ",";
			json << newV.tgt.x << "," << newV.tgt.y << "," << newV.tgt.z << ",";
			json << newV.uv.x << "," << newV.uv.y;// << ",";
			/*color is for testing only*/
			//json << newV.col.x << "," << newV.col.y << "," << newV.col.z << "," << newV.col.w;
			//json << "]";

			if (i + 1 != nVertices){
				json << ",";
			}
		}
		json << "],";

		fscanf(file, "%*s %d\n", &nIndices);
		json << "\"indicesCount\":" << nIndices << ",";
		
		json << "\"indicesData\":[";
		int a, b, c;
		for (int i = 0; i < nIndices; i += 3){
			fscanf(file, "%*s %d, %d, %d\n", &a, &b, &c);
			json << a << "," << b << "," << c;
			if (i + 3 != nIndices){
				json << ",";
			}
		}
		json << "]";

		json << "}";
		return true;
	}
	else{
		perror("Error");
	}
	return false;
}

