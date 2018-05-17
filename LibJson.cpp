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

void Json::clearJS(void)
{
   data_.clear();
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

	typeJD name = path;

	file.open(name.c_str());
	if(!file.is_open())return false;

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
			 if (svalue == "") throw 1;
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
	return true;
}
bool Json::load(const typeJD& path)
{
  std::ifstream file;
  typeJD s;

  file.open(path.c_str());
  if(!file.is_open())return false;

  bool isMain = false;
  bool isParam = false;
  bool isKey   = true;

  typeJD key;
  std::vector<typeJD> params;

  for(file >> s; !file.eof(); file >> s)
  {
	  if(s == "{")
	  {
		if(isMain)isParam = true;
		else isMain = true;
		continue;

	  }
	  if(s == "}")
	  {
		if(isParam){
			isParam = false;
			data_[key] = params;
			key.clear();
			params.clear();
			continue;
		}
		else{
			if(isMain)break;
		}

	  }

	  if(isParam)
	  {
		params.push_back(pars(s));

	  }
	  else
	  {
		if (isKey) {
			key = pars(s);
			isKey = false;
		}
		else{
			params.push_back(pars(s));
			isKey = true;
			data_[key] = params;

			key.clear();
			params.clear();
		}


	  }
  }


  file.close();
  return true;

}
std::vector<std::pair<typeJD, typeJD> > Json::getPairs()
{
   std::vector<std::pair<typeJD, typeJD> > temp;
   std::pair<typeJD, typeJD> pairs;
   MapJSON::iterator it;

   for(it = data_.begin(); it != data_.end(); ++it)
   {
	   pairs.first =  it->first;
	   pairs.second = it->second.at(0);
	   temp.push_back(pairs);
   }
   return temp;
}
std::vector<typeJD> Json::getParam(const typeJD& key)
{
   std::vector<typeJD> temp;
   MapJSON::iterator it = data_.find(key);
   if(it == data_.end())return temp;
   else return data_[key];
}
typeJD Json::pars(typeJD data)
{
  return data.substr(1,data.length()-3);
}

