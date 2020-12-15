
#include "platspub.h"
#include "json/json.h"

#include <iostream>   
#include <fstream>   
using namespace std;   
   
int ParseJsonFromFile(const char* filename,Json::Value& vaRoot)
{
  // 解析json用Json::Reader
  Json::Reader reader;
  // Json::Value是一种很重要的类型，可以代表任意类型。如int, string, object, array...
  Json::Value root;       

  std::ifstream is;
  is.open (filename, std::ios::binary );  
  if (reader.parse(is, root))
  {
    std::string code;
    if (!root["files"].isNull())  // 访问节点，Access an object value by name, create a null member if it does not exist.
      code = root["uploadid"].asString();
    
    // 访问节点，Return the member named key if it exist, defaultValue otherwise.
    code = root.get("uploadid", "null").asString();

    // 得到"files"的数组个数
    int file_size = root["files"].size();

    // 遍历数组
    for(int i = 0; i < file_size; ++i)
    {
      Json::Value val_image = root["files"][i]["images"];
      int image_size = val_image.size();
      for(int j = 0; j < image_size; ++j)
      {
        std::string type = val_image[j]["type"].asString();
        std::string url = val_image[j]["url"].asString();
      }
    }
  }
  is.close();
  

    
  vaRoot = root;
  
  return 0;
}   
   
int main (int argc, char *argv[])
{
    printf("json ddtest\n");
    
    const char* str = "{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";  
    
    Json::Reader reader;  
    Json::Value root;  
    if (reader.parse(str, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素  
    {  
        std::string upload_id = root["uploadid"].asString();  // 访问节点，upload_id = "UP000000"  
        int code = root["code"].asInt();    // 访问节点，code = 100  
        
        // 转换为字符串（带格式）  
        std::string out = root.toStyledString();  
        
        //cout<< out <<endl;
        printf("%s\n",out.c_str());
        
    }  
    
    Json::Value vaRoot;
    if(ParseJsonFromFile("./ddtest.json",vaRoot) ==0 )
    {
        // 输出无格式json字符串  
        Json::FastWriter writer;  
        std::string out1 = writer.write(vaRoot);  
        cout<< out1 <<endl;
    
        //在json结构中插入json
        Json::Value arrayObj;   // 构建对象  
        Json::Value new_item, new_item1;  
        new_item["date"] = "2014-3-18";  
        new_item1["time"] = "10:31:36";  
        arrayObj.append(new_item);  // 插入数组成员  
        arrayObj.append(new_item1); // 插入数组成员  
        int file_size = vaRoot["files"].size();  
        for(int i = 0; i < file_size; ++i)  
          vaRoot["files"][i]["exifs"] = arrayObj;   // 插入原json中      
    
    
         // 转换为字符串（带格式）  
        std::string out2 = vaRoot.toStyledString();  
        cout<< out2 <<endl;
        
        
        
    
    }
    
    return 0;      


}


