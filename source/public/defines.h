#pragma once

#ifndef JCON_NAMESPACE
#define JCON_NAMESPACE jconsole
#endif

#ifndef JCON_BUFFER_SIZE
#define JCON_BUFFER_SIZE 255
#endif

#ifndef JCON_DEFAULT_FONT
#define JCON_DEFAULT_FONT "../../resources/fonts/Consolas.ttf"
#endif

#ifdef JCON_EXPORTS
#  define JCON_API __declspec(dllexport)
#else
#  define JCON_API __declspec(dllimport)
#endif