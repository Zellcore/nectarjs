/*
 * This file is part of NectarJS
 * Copyright (c) 2017 - 2020 Adrien THIERRY
 * http://nectarjs.com - https://seraum.com/
 *
 * sources : https://github.com/nectarjs/nectarjs
 * 
 * NectarJS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarJS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarJS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
#if defined(_WIN32)  || defined(__CYGWIN__)
  #define WIN32_LEAN_AND_MEAN
  #include "windows.h"
#endif

#include "httplib.h"

using namespace httplib;


var __NJS_HTTP_LISTEN(var _host, var _port, var _cb, var _opt)
{
	Server __NJS_HTTP_SRV;
	
	if(_opt.type == NJS::Enum::Type::Object)
	{
		var _static = _opt["static"];
		if(_static.type == NJS::Enum::Type::String) 
		{
			auto ret = __NJS_HTTP_SRV.set_mount_point("/", ((std::string)_static).c_str());
			if (!ret) 
			{
			  __NJS_Log_Console("Warning: path " + _static + " doesn't exist");
			}
		}
		
	}
  /*** LOAD GET ***/
  __NJS_HTTP_SRV.Get(".*", [&](const Request& request, Response& response)
  {

	var __f_NJS_HTTP_RES_END = __NJS_Create_Var_Scoped_Anon(
	{
		var _str = "";
		if(__NJS_VARLENGTH == 1) _str = __NJS_VARARGS[0];
		response.set_content((std::string)_str, "text/plain");
		return var();
	});
	

	var _req = __NJS_Create_Object();
	_req["method"] = "GET";
	_req["url"] = request.path;
    
	var _query = __NJS_Create_Object();
	for (auto it = request.params.begin(); it != request.params.end(); ++it)
	{
	  __NJS_Object_Set(it->first, it->second, _query);
	}
	_req["get"] = _query;

	var _njs_res = __NJS_Create_Object();
	_njs_res["end"] = __f_NJS_HTTP_RES_END;

	_cb(_req, _njs_res);
	return var();
  });
  
  /*** LOAD POST ***/
  __NJS_HTTP_SRV.Post(".*", [&](const Request& request, Response& response, const ContentReader &content_reader)
  {
	NJS::Type::function_t* __NJS_HTTP_RES_END = new NJS::Type::function_t([&](NJS::VAR& __NJS_THIS, NJS::VAR* _args, int _length)
	{
		var _str = "";
		if(_length == 1) _str = _args[0];
		response.set_content((std::string)_str, "text/plain");
		return var();
	});
	var __f_NJS_HTTP_RES_END = __NJS_Create_Function(__NJS_HTTP_RES_END);

    var _req = __NJS_Create_Object();
	_req["method"] = "POST";
	_req["url"] = request.path;
    
    // GET DATA
    if (request.is_multipart_form_data()) 
    {
      __NJS_Object_Set("isMultipart", true, _req);
      var _multi = __NJS_Create_Object();

      MultipartFormDataItems files;
      content_reader(
              [&](const MultipartFormData &file)
              {
                      files.push_back(file);
                      return true;
              },
              [&](const char *data, size_t data_length)
              {
                      files.back().content.append(data, data_length);
                      return true;
              }
      );
      for (const auto &file : files)
      {
        var _file = __NJS_Create_Object();
		_file["body"] = file.content;
		_file["mime"] = file.content_type;
		_multi[file.name] = _file;
      }
	  _req["data"] = _multi;
    } 
    else 
    {
		_req["isMultipart"] = false;
      std::string body;
      content_reader([&](const char *data, size_t data_length) 
      {
        body.append(data, data_length);
        return true;
      });
      _req["data"] = body;
    }
    
    
    var _njs_res = __NJS_Create_Object();
	_njs_res["end"] = __f_NJS_HTTP_RES_END;
    
    _cb(_req, _njs_res);
    return var();
  });
  
  /*** LOAD PUT ***/
  __NJS_HTTP_SRV.Put(".*", [&](const Request& request, Response& response, const ContentReader &content_reader)
  {
	NJS::Type::function_t* __NJS_HTTP_RES_END = new NJS::Type::function_t([&](NJS::VAR& __NJS_THIS, NJS::VAR* _args, int _length)
	{
		var _str = "";
		if(_length == 1) _str = _args[0];
		response.set_content((std::string)_str, "text/plain");
		return var();
	});
	var __f_NJS_HTTP_RES_END = __NJS_Create_Function(__NJS_HTTP_RES_END);

    var _req = __NJS_Create_Object();
	_req["method"] = "PUT";
	_req["url"] = request.path;
    
    // GET DATA
    if (request.is_multipart_form_data()) 
    {
		_req["isMultipart"] = true;
      var _multi = __NJS_Create_Object();

      MultipartFormDataItems files;
      content_reader(
              [&](const MultipartFormData &file)
              {
                      files.push_back(file);
                      return true;
              },
              [&](const char *data, size_t data_length)
              {
                      files.back().content.append(data, data_length);
                      return true;
              }
      );

      for (const auto &file : files)
      {
        var _file = __NJS_Create_Object();
		_file["body"] = file.content;
		_file["mime"] = file.content_type;
		_multi[file.name] = _file;
      }
	  _req["data"] = _multi;
    } 
    else 
    {
		_req["isMultipart"] = false;
      std::string body;
      content_reader([&](const char *data, size_t data_length) 
      {
        body.append(data, data_length);
        return true;
      });
      _req["data"] = body;
    }
    
    var _njs_res = __NJS_Create_Object();
	_njs_res["end"] = __f_NJS_HTTP_RES_END;
    
    _cb(_req, _njs_res);
    return var();
  });
  
  /*** LOAD DELETE ***/
  __NJS_HTTP_SRV.Delete(".*", [&](const Request& request, Response& response)
  {
	NJS::Type::function_t* __NJS_HTTP_RES_END = new NJS::Type::function_t([&](NJS::VAR& __NJS_THIS, NJS::VAR* _args, int _length)
	{
		var _str = "";
		if(_length == 1) _str = _args[0];
		response.set_content((std::string)_str, "text/plain");
		return var();
	});
	var __f_NJS_HTTP_RES_END = __NJS_Create_Function(__NJS_HTTP_RES_END);

    var _req = __NJS_Create_Object();
	_req["method"] = "DELETE";
	_req["url"] = request.path;
    
    var _njs_res = __NJS_Create_Object();
	_njs_res["end"] = __f_NJS_HTTP_RES_END;

    _cb(_req, _njs_res);
    return var();
  });
  
  __NJS_HTTP_SRV.listen(((std::string)_host).c_str(), (int)_port);
  return var();
}

