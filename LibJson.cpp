//---------------------------------------------------------------------------

#pragma hdrstop

#include "LibJson.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace ZAA;
Json::Json()
{
//
}
Json::~Json()
{
//
}
void Json::setValue(typeJD key, typeJD value)
{
	data_[key].clear();
	data_[key].push_back(value);
}
void Json::setList(typeJD key, const std::vector<typeJD>& list)
{
	data_[key] = list;
}
bool Json::save(const typeJD& path)
{
	std::ofstream file;
	file.open("file.json");
	file << "{" << std::endl;
	typeJD item = "  ";

	MapJSON::iterator it = data_.begin();

	bool last = false;
	for(; it != data_.end(); ++it)
	{
	  if(last){file << "\," <<std::endl;}
	  else last = true;

	  size_t countValue = it->second.size();
	  if(countValue == 1)
	  {
		file << item <<"\""<< it->first<<"\"\: \""
		   << it->second.at(0)<< "\"";
	  }
	  else
	  {
		 file << item <<"\""<< it->first<<"\"" << "\: {" << std::endl;

		 std::vector<typeJD>::iterator br = it->second.begin();
		 bool slast = false;
         bool ret   = false;
		 std::string skey, svalue;


		 for(; br != it->second.end(); ++br)
		 {
		   if(slast) {file << "\," <<std::endl;}
		   else slast = true;
		   skey = *br;

		   try{
			 svalue = *(++br);
		   }catch(...)
		   { svalue = "NULL"; ret = true; }

		   file << item << item << item << "\"" << skey << "\"\: \"" << svalue <<"\"";

           if(ret)break;
		 }
		 file << std::endl;
		 file << item <<"}";
	  }
	}
	file << std::endl;
	file << "}" << std::endl;

	file.close();
}
bool Json::load(const typeJD& path)
{
//
}
std::vector<std::pair<typeJD, typeJD> > Json::getPairs()
{
///
}
typeJD Json::getParam(const typeJD& key)
{
//
}
