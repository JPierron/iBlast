#ifndef _SERIALIZER_
# define _SERIALIZER_

template <class T>
class			Serializer
{
	T		_data;
	char	_binaryData[512];
public:
	Serializer()
	{
		memset(_binaryData, 0, sizeof(T) + 1);
	}
	~Serializer() {}

	//getter setter
	void	SData(const T& data)
	{ this->_data = data; }

	T&		GData()
	{ return this->_data; }

	void	SBinData(char* binaryData)
	{ memcpy(this->_binaryData, binaryData, sizeof(this->_binaryData)); }

	char*	GBinData()
	{ return this->_binaryData; }

	//serialise les donnees de _data dans _binaryData
	void	Serialize()
	{
		char*	tmpBin = reinterpret_cast< char* >(&this->_data);
		memcpy((void*)this->_binaryData, (void*)tmpBin, sizeof(this->_binaryData));
	}

	//deserialise les donnees de _binaryData dans _data
	void	UnSerialize()
	{
		this->_data = reinterpret_cast< T& >(*this->_binaryData);
	}

	//serialise les donnees externes de data dans _binaryData
	void	Serialize(T& data)
	{
		char*	tmpBin = reinterpret_cast< char* >(&data);
		memcpy((void*)this->_binaryData, (void*)tmpBin, sizeof(this->_binaryData));
	}

	//deserialise les donnees externe de binaryData dans _data
	void	UnSerialize(const char* binaryData)
	{
		this->_data = reinterpret_cast< T& >(*binaryData);
	}
};

#endif // _SERIALIZER_
