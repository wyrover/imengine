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

#include "online/rpc_online_service.h"

#include "proto/api_message_box.h"

#include "online/online_session_manager.h"

ProtoRpcResponsePtr DoClientOnline(RpcRequestPtr request) {
  auto req = ToApiRpcRequest<zproto::ClientOnlineReq>(request);
  LOG(INFO) << (*req)->Utf8DebugString();

  auto online_manager = OnlineSessionManager::GetInstance();
  online_manager->AddEntry(static_cast<uint16_t>((*req)->server_id()),
                           (*req)->conn_id(),
                           (*req)->app_id(),
                           (*req)->user_id(),
                           static_cast<uint16_t>((*req)->state()));
  
  auto rsp = std::make_shared<ApiRpcOk<zproto::ClientOnlineRsp>>();
  rsp->set_req_message_id(request->message_id());
  (*rsp)->set_index_id(1234);
  
  return rsp;
}

ProtoRpcResponsePtr DoClientOffline(RpcRequestPtr request) {
  auto req = ToApiRpcRequest<zproto::ClientOfflineReq>(request);
  LOG(INFO) << (*req)->Utf8DebugString();
 
  auto online_manager = OnlineSessionManager::GetInstance();
  online_manager->RemoveEntryBySessionID(static_cast<uint16_t>((*req)->server_id()),
                                         (*req)->conn_id());
  
  auto rsp = std::make_shared<ApiRpcOk<zproto::ClientOfflineRsp>>();
  rsp->set_req_message_id(request->message_id());
  (*rsp)->set_index_id(1234);

  return rsp;
}

ProtoRpcResponsePtr DoQueryOnlineUser(RpcRequestPtr request) {
  auto req = ToApiRpcRequest<zproto::QueryOnlineUserReq>(request);
  LOG(INFO) << (*req)->Utf8DebugString();
  
  auto online_manager = OnlineSessionManager::GetInstance();
  
  std::list<std::string> app_user_id_list;
  SessionEntryList sessions;
  
  for (int i=0; i<(*req)->user_id_list_size(); ++i) {
    std::string app_user_id = (*req)->user_id_list(i).user_id() + "@" + folly::to<std::string>((*req)->user_id_list(i).app_id());
    app_user_id_list.push_back(app_user_id);
  }
  
  online_manager->LookupEntrysByUserIDList(app_user_id_list, &sessions);
  
  auto rsp = std::make_shared<ApiRpcOk<zproto::QueryOnlineUserRsp>>();
  rsp->set_req_message_id(request->message_id());

  for (auto& v : sessions) {
    auto online_user = (*rsp)->add_online_users();
    online_user->set_app_id(v.app_id);
    online_user->set_user_id(v.user_id);
    online_user->set_server_id(v.server_id);
    online_user->set_conn_id(v.session_id);
  }
  
  return rsp;
}

