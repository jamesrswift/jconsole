#pragma once

#define JCON_DEF_ACCESSORFUNC( type, privateName, publicName )\
	public:\
		type get##publicName( );\
		void set##publicName( type NewValue );\
	private:\
		type privateName;

#define JCON_IMPL_ACCESSORFUNC( parent, type, privateName, publicName )\
	type parent::get##publicName( ){ return this->##privateName; }\
	void parent::set##publicName( type NewValue ){ this->##privateName = NewValue; }