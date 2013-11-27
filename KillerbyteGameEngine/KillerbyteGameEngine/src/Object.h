// Base Object Super Class

#ifndef OBJECT_H
#define OBJECT_H

namespace KillerbyteGameEngine
{
	class Object
	{
	public:
		void setID(unsigned int newID) { id = newID; }
		unsigned int getID() { return id; }
	protected:
		Object() { }
		virtual ~Object() { }
	private:
		unsigned int id;
	};
}

#endif