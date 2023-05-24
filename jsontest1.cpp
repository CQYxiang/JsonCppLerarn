#include <iostream>
#include <json/json.h>
#include <string>
#include <fstream>
#include <ostream>
#include <typeinfo>
/*
[
	"lol",20,90,false,
	["ace":"dema"],
	{"sex":"666","girlfriend":"guanghui"}
]
*/
void writeJson() {
	Json::Value root;
	root.append("lol");
	root.append(20);
	root.append(90);
	root.append(false);

	Json::Value subArray;
	subArray.append("ace");
	subArray.append("dema");
	root.append(subArray);

	Json::Value obj;
	obj["sex"] = "666";
	obj["girlfriend"] = "guanghui";
	root.append(obj);

#if 1
	std::string jsondata = root.toStyledString();
#else
	Json::FastWriter w;
	std::string json = w.write(root);
#endif
	std::ofstream ofs("test.json");
	ofs << jsondata;
	ofs.close();
}

void readJson() {
	std::ifstream ifs("test.json");
	Json::Reader rd;
	Json::Value root;
	rd.parse(ifs, root);//读ifs流对象到json创建的对象

	std::cout << typeid(root).name() << std::endl;
	for (unsigned i = 0; i < root.size(); i++) {
		Json::Value item = root[i];
		std::cout<<i<<"\t" << root[i] << std::endl;
		//如果是个列表（数组）
		if (item.isArray()) {
			for (unsigned j = 0; j < item.size(); j++) {
				std::cout << i << "\t" << root[i][j].asString() << std::endl;
			}
		}
		//如果是个json::Value对象
		else if(item.isObject()) {
			Json::Value::Members keys = item.getMemberNames();
			for (int j = 0; j < keys.size(); j++) {
				std::cout<< i << "\t" << keys.at(j)<<"\t:\t"<<item[keys[j]] << std::endl;
			}
		}
	}
	ifs.close();
}

int main() {
	//writeJson();
	readJson();
}

