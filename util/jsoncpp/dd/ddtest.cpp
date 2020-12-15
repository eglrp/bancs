
#include "platspub.h"
#include "json/json.h"

#include <iostream>   
#include <fstream>   
using namespace std;   
   
int ParseJsonFromFile(const char* filename,Json::Value& vaRoot)
{
  // ����json��Json::Reader
  Json::Reader reader;
  // Json::Value��һ�ֺ���Ҫ�����ͣ����Դ����������͡���int, string, object, array...
  Json::Value root;       

  std::ifstream is;
  is.open (filename, std::ios::binary );  
  if (reader.parse(is, root))
  {
    std::string code;
    if (!root["files"].isNull())  // ���ʽڵ㣬Access an object value by name, create a null member if it does not exist.
      code = root["uploadid"].asString();
    
    // ���ʽڵ㣬Return the member named key if it exist, defaultValue otherwise.
    code = root.get("uploadid", "null").asString();

    // �õ�"files"���������
    int file_size = root["files"].size();

    // ��������
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
    if (reader.parse(str, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��  
    {  
        std::string upload_id = root["uploadid"].asString();  // ���ʽڵ㣬upload_id = "UP000000"  
        int code = root["code"].asInt();    // ���ʽڵ㣬code = 100  
        
        // ת��Ϊ�ַ���������ʽ��  
        std::string out = root.toStyledString();  
        
        //cout<< out <<endl;
        printf("%s\n",out.c_str());
        
    }  
    
    Json::Value vaRoot;
    if(ParseJsonFromFile("./ddtest.json",vaRoot) ==0 )
    {
        // ����޸�ʽjson�ַ���  
        Json::FastWriter writer;  
        std::string out1 = writer.write(vaRoot);  
        cout<< out1 <<endl;
    
        //��json�ṹ�в���json
        Json::Value arrayObj;   // ��������  
        Json::Value new_item, new_item1;  
        new_item["date"] = "2014-3-18";  
        new_item1["time"] = "10:31:36";  
        arrayObj.append(new_item);  // ���������Ա  
        arrayObj.append(new_item1); // ���������Ա  
        int file_size = vaRoot["files"].size();  
        for(int i = 0; i < file_size; ++i)  
          vaRoot["files"][i]["exifs"] = arrayObj;   // ����ԭjson��      
    
    
         // ת��Ϊ�ַ���������ʽ��  
        std::string out2 = vaRoot.toStyledString();  
        cout<< out2 <<endl;
        
        
        
    
    }
    
    return 0;      


}


