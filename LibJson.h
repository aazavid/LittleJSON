//---------------------------------------------------------------------------

#ifndef LibJsonH
#define LibJsonH

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

//---------------------------------------------------------------------------

namespace ZAA{

	typedef std::string typeJD;
	typedef std::map<typeJD, std::vector<typeJD> > MapJSON;

	class Json
	{
		public:

		Json();
		~Json();
		void setValue(typeJD key, typeJD value);
		void setList(typeJD key, const std::vector<typeJD>& list);
		bool save(const typeJD& path);
		bool load(const typeJD& path);
		std::vector<std::pair<typeJD, typeJD> >getPairs();
		typeJD getParam(const typeJD& key);

	private:

		MapJSON data_;

	};

};
#endif
