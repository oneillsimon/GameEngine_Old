#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include <string>
#include <vector>

#include "Lua.h"

class ScriptManager
{
private:
	lua_State* m_L;
	std::string m_scriptName;

	std::vector<std::string> m_otherCode;
	std::vector<std::string> m_localCode;
	std::vector<std::string> m_updateCode;

public:
	ScriptManager();
	~ScriptManager();

	enum
	{
		FUNC_INPUT,
		FUNC_UPDATE,
		FUNC_RENDER,
		FUNC_OTHER
	};

	void addFunctionCode(const std::string& code, int function);
	void addLocalCode(const std::string& code);

	void generateFunctionBody(std::ifstream& file, int function, const std::string& functionDeclartion = "");

	template<class T>
	void setGlobal(T t, const std::string& name)
	{
		luabridge::setGlobal(m_L, t, name.c_str());
	}

	void generateScriptName(void* object);

	void setFunctionCode(const std::string& code, int index, int function);
	void setLocalCode(const std::string& code, int index);

	lua_State* getL();

	std::string getScriptName() const;

	std::vector<std::string> getFunctionCode(int function) const;
	std::vector<std::string> getLocalCode() const;
};

#endif