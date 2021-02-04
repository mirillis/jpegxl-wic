//----------------------------------------------------------------------------
//
// Copyright 2021 Mirillis
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//----------------------------------------------------------------------------

#ifndef __MRLSJXLCODECWICINTERFACE_H
#define __MRLSJXLCODECWICINTERFACE_H


// CLSID JXL DECODER
// {0AF8C503-8682-4FBD-AA76-22F7E5567A4F}
static const GUID CLSID_JXLDecoder =
{ 0xaf8c503, 0x8682, 0x4fbd, { 0xaa, 0x76, 0x22, 0xf7, 0xe5, 0x56, 0x7a, 0x4f } };


// CLSID JXL ENCODER
// {99F21B6A-4098-4A14-8F92-26C21F119F2D}
static const GUID CLSID_JXLEncoder =
{ 0x99f21b6a, 0x4098, 0x4a14, { 0x8f, 0x92, 0x26, 0xc2, 0x1f, 0x11, 0x9f, 0x2d } };


// GUID JXL CONTAINER FORMAT
// {32FEBF67-29D8-4643-BE1E-5F279F6BD7C6}
static const GUID GUID_ContainerFormatJXL =
{ 0x32febf67, 0x29d8, 0x4643, { 0xbe, 0x1e, 0x5f, 0x27, 0x9f, 0x6b, 0xd7, 0xc6 } };


// GUID VENDOR MIRILLIS
// {8897BFED-CDE6-40AA-9571-4883EF4208B5}
static const GUID GUID_VendorMirillis =
{ 0x8897bfed, 0xcde6, 0x40aa, { 0x95, 0x71, 0x48, 0x83, 0xef, 0x42, 0x8, 0xb5 } };


// GUID PROPERTY STORE
// {5CC0FB5D-9564-4BE6-A6FD-8BA365D813EB}
static const GUID GUID_PropertyStoreJXL = 
{ 0x5cc0fb5d, 0x9564, 0x4be6, { 0xa6, 0xfd, 0x8b, 0xa3, 0x65, 0xd8, 0x13, 0xeb } };

#endif
