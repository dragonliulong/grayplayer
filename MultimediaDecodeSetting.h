#ifndef MULTIMEDIADECODESETTING_H
#define MULTIMEDIADECODESETTING_H

#include <vector>
#include "MultimediaVD3D9.h"
#include "MultimediaVD3D11.h"
using namespace std;

enum DecodeMode
{
    SOFTWARE,
    DXVA2,
    D3D11VA,
};

enum RenderMode
{
    D3D9,
    D3D11,
};

//
extern vector<IDXGIAdapter*> adapters;
extern const int adapter_count;
extern const DXGI_FORMAT dxgi_formats[5];
extern const DXGI_SWAP_EFFECT dxgi_swap_effects[4];

//------------------------------榛樿璁剧疆---------------------------------

extern const DecodeMode decodeModeDef;
extern const RenderMode renderModeDef;

extern const int sw_thread_count_def;
extern const bool flipex_mode_def;
extern const int adapter_choice_def;
extern const DXGI_FORMAT dxgi_format_def;
extern const int swap_chain_count_def;
extern const DXGI_SWAP_EFFECT dxgi_swap_effect_def;

//----------------------------------------------------------------------

extern DecodeMode decodeMode;
extern RenderMode renderMode;

//杞В鐨勭嚎绋嬫暟
extern int sw_thread_count;

//D3D9 flipex妯″紡
extern bool flipex_mode;

//D3D11VA
extern int adapter_choice;
extern DXGI_FORMAT dxgi_format;
extern int swap_chain_count;
extern DXGI_SWAP_EFFECT dxgi_swap_effect;


#endif // MULTIMEDIADECODESETTING_H
