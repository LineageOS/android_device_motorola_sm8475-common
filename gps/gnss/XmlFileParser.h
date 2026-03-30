/*
Copyright (c) 2023-2024 Qualcomm Innovation Center, Inc. All rights reserved.
SPDX-License-Identifier: BSD-3-Clause-Clear
*/

#ifndef XML_FILE_PARSER_H
#define XML_FILE_PARSER_H
#include <stdint.h>
#include <sys/types.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <vector>
#include "LocationDataTypes.h"
using namespace std;

typedef xmlDoc* (*xmlParseMemoryFuncT)(const char*, int);
typedef xmlNode* (*xmlDocGetRootElementFuncT)(xmlDoc*);
typedef void (*xmlFreeDocFuncT)(xmlDocPtr);
typedef void (*xmlCleanupParserFuncT)();
typedef int (*xmlStrncmpFuncT)(const xmlChar*, const xmlChar*, int);
typedef int (*xmlStrlenFuncT)(const xmlChar*);
typedef xmlChar* (*xmlNodeGetContentFuncT)(const xmlNode*);

struct XmlParserInterface {
    xmlParseMemoryFuncT xmlParseMemoryFunc = nullptr;
    xmlDocGetRootElementFuncT xmlDocGetRootElementFunc = nullptr;
    xmlFreeDocFuncT xmlFreeDocFunc = nullptr;
    xmlCleanupParserFuncT xmlCleanupParserFunc = nullptr;
    xmlStrncmpFuncT xmlStrncmpFunc = nullptr;
    xmlStrlenFuncT xmlStrlenFunc = nullptr;
    xmlNodeGetContentFuncT xmlNodeGetContentFunc = nullptr;
};
int loc_read_conf_xml(const char* buffer, int bufLen,
        mgpOsnmaPublicKeyAndMerkleTreeStruct* merkle_tree);

#endif // XML_FILE_PARSER_H
