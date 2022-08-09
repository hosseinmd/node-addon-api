#include <napi.h>
#include <iostream>
#include <sstream>
#include "GetSepidz.h"

Napi::Object CreateObject(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Object obj = Napi::Object::New(env);

  Invoice invoice = GetSepidz();

  obj.Set(Napi::String::New(env, "price"), Napi::String::New(env,  invoice.price));
  obj.Set(Napi::String::New(env, "costumerCode"), Napi::String::New(env,  invoice.costumerCode));
  obj.Set(Napi::String::New(env, "costumerName"), Napi::String::New(env,  invoice.costumerName));
  obj.Set(Napi::String::New(env, "phoneNumber"), Napi::String::New(env,  invoice.phoneNumber));
  obj.Set(Napi::String::New(env, "operatorName"), Napi::String::New(env,  invoice.operatorName));
  obj.Set(Napi::String::New(env, "isElementFound"), Napi::Boolean::New(env,  invoice.isElementFound));

  return obj;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  return Napi::Function::New(env, CreateObject, "createObject");
}

NODE_API_MODULE(addon, Init)
