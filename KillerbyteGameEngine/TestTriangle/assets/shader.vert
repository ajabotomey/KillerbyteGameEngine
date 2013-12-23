uniform mat4 MVPMatrix;
attribute vec4 vPosition;

void main(void)
{
	gl_Position = MVPMatrix * vPosition;
}