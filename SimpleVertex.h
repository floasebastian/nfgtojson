struct Vector2{
	float x;
	float y;
};

struct Vector3{
	float x;
	float y;
	float z;
};

struct Vector4{
	float x;
	float y;
	float z;
	float w;

};

struct Vertex
{
	Vector3 pos;
	Vector3 norm;
	Vector3 binorm;
	Vector3 tgt;
	Vector2 uv;
	//Vector4 col; //color for testing
};
