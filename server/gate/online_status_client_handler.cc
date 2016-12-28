/*
 *  Copyright (c) 2016, https://github.com/nebula-im/imengine
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

#include "gate/online_status_client_handler.h"

#include "base/message_handler_util.h"

int OnlineStatusClientHandler::OnNewConnection() {
  // 连接建立成功，同步在线状态
  return 0;
}

int OnlineStatusClientHandler::OnDataReceived(std::shared_ptr<PackageMessage> message_data) {
  // 当前只收不处理
  LOG(INFO) << "OnDataReceived - recv message_data: " << message_data->ToString();
  return 0;
}

int OnlineStatusClientHandler::OnConnectionClosed() {
  return 0;
}
