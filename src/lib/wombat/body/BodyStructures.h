#ifndef BODYSTRUCTURES_H
#define BODYSTRUCTURES_H



namespace wombat
{

struct Identifier
{
		Identifier() : parent(0){}
		unsigned long timestamp; // current time
		unsigned long identifier;
		Identifier *parent; // pointer to parrent
};


}


#endif // BODYSTRUCTURES_H
