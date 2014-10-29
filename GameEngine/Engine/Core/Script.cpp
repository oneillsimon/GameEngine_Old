#include "Script.h"
#include "Math3D.h"

static void injectIntoLua(lua_State* luaState, GameObject* t);

Script::Script(const std::string& script) :
	scriptName("Engine/Scripts/" + script)
{
	L = luaL_newstate();
	luaL_openlibs(L);

	Math3D::registerMembers("Math", L);
	Transform::registerMembers("Core", L);

	if(luaL_dofile(L, scriptName.c_str()))
	{
		const char* err = lua_tostring(L, -1);
		printf("%s\n", err);
	}
}

Script::~Script()
{
}

void Script::input(const Input& input, float delta)
{
}

void Script::update(float delta)
{
	luabridge::setGlobal(L, m_parent->getTransform(), "transform");

	lua_getglobal(L, "update");

	if(lua_isfunction(L, lua_gettop(L)))
	{
		lua_call(L, 0, 0);
	}

	Transform t = (Transform)luabridge::getGlobal(L, "transform");
	Vector3 p = t.getPosition();
	Quaternion r = t.getRotation();
	Vector3 s = t.getScale();
	
	m_parent->getTransform()->setPosition(p);
	m_parent->getTransform()->setRotation(r);
	m_parent->getTransform()->setScale(s);
}

void Script::render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const
{
}