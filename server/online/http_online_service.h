/*
 *  Copyright (c) 2016, https://github.com/zhatalk
 *  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef	ONLINE_HTTP_ONLINE_SERVICE_H_
#define	ONLINE_HTTP_ONLINE_SERVICE_H_

#include "nebula/net/handler/http/http_request_handler.h"

void Query(const proxygen::HTTPMessage& headers, folly::IOBufQueue*, proxygen::ResponseBuilder* r);


#endif // ONLINE_HTTP_ONLINE_SERVICE_H_

