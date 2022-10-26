#ifndef CHAT_STATUS_H
#define CHAT_STATUS_H

typedef enum {
    Chat_Login,             // 로그인(서버 접속)   --> 채팅방 입장 위한 정보 저장
    Chat_In,                // 채팅방 입장
    Chat_Talk,              // 채팅
    Chat_Out,               // 채팅방 퇴장         --> 초대 가능
    Chat_LogOut,            // 로그 아웃(서버 단절) --> 초대 불가능
    Chat_Invite,            // 초대
    Chat_KickOut,           // 강퇴
    Chat_List,              // 현재 채팅방 참여목록
} Chat_Status;

#endif // CHAT_STATUS_H
