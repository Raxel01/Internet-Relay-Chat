#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <iostream>
#include <deque>
#include <vector>
#include <map>
#include <algorithm>
#include <unistd.h>

class MYhost
{
    public :
    static std::string GetHost();
};

std::string MYhost::GetHost()
{
        char TheHost[256];
        int status;

        status = gethostname(TheHost, sizeof(TheHost));
        if (status == -1){
            std::cout << strerror(errno) << std::endl;
            // exit(1);
            throw std::runtime_error("Trouble when Getting your hostname");
        }
    return (TheHost);
}

/*CHANNEEEEEL OPERATIONS AND CLASS******************************************************/
typedef std::deque<std::string> DEQUE ;

class CLIENTD{ // Will Be replaced By The Client getted From mol Server 
    public :
        std::string nickname;
        std::string username;
        std::string ipAddress;
        CLIENTD(std::string Setnickname, std::string Setusername, std::string Setip);
};

class ClientGlobal // Will Be replaced To By my Own class
{
    public :
        static std::map<int, CLIENTD> ServerClients;
};

std::map<int, CLIENTD> ClientGlobal::ServerClients;// ok ok ok 

CLIENTD::CLIENTD(std::string Setnickname, std::string Setusername, std::string Setip) : nickname(Setnickname), username(Setusername), ipAddress(Setip)
{}

class ChatRoom
{
    public :
        const std::string     _RoomName         ;
        std::string           _ChatTopic        ;
        DEQUE                _Members           ;
        DEQUE                _BannedUsers       ;
        DEQUE                _Mediators         ;
        DEQUE                _InviteList        ;
        std::string           _ChatKey          ;
        size_t               _AllowedUsers      ; //Limit Setted;
        bool                 _Acces_isInviteOnly;
        bool                 keyStatus          ; //+k if the key is setted or not 
        bool                 HaveLimitUser      ; //+l
        bool                 TopicRestriction   ;   //+t [+t] seTtoknow Who will seet the Topic
    public :
        ChatRoom();
        ChatRoom(std::string& Creator,std::string& SetRoomName);
        
        void            Addasmember(std::string& newMember);
        void            AddasMediator(std::string& NewMediator);
        
        void            removeMember(std::string& tobeRemoved);
        void            removeMediator(std::string& toBeremoved);

        bool            IsalreadyMember(std::string& MayUser);
        bool            IsMediator(std::string& MayMediator);
        bool            IsBanned(std::string& MayBanned);
        bool            IsInviteList(std::string& TargetUser);
        std::string     MembersList();
        void            getelems();
        const std::string&    GetRoomname(){
    return _RoomName;
}    
        ~ChatRoom(); 
};

void            ChatRoom::getelems(){
    DEQUE::iterator it = _Mediators.begin();
    
    while (it != _Mediators.end()){
        std::cout << "Mediator : " << *it<< std::endl;
        it++;
    }
    std::cout << "^^^^^^^^^^^Mediator^^^^^^^^^" << std::endl;
    it = _Members.begin();
    while (it != _Members.end()){
        std::cout << "mEMBER : " << *it<< std::endl;
        it++;
    }
    std::cout << "^^^^^^^^^^^Members^^^^^^^^^" << std::endl;
    std::cout << "RoomNAME => " << _RoomName << std::endl;

    std::cout << "Keysstatus : " << keyStatus << std::endl;  
    std::cout << "Users Joined Channel " << _Mediators.size() + _Members.size() << std::endl;
    std::cout << "_____________________________________________________________"<< std::endl;
}

std::string     ChatRoom::MembersList(){
    std::string list(":");
    int i = -1;
    while (++i < _Mediators.size()){
        list+= _Mediators.at(i) + " "; 
    }
    i = -1;
    while (++i < _Members.size()){
        list+= _Members.at(i) + " ";
    }
    return list;
}

void    ChatRoom::Addasmember(std::string& newMember){
    this->_Members.push_back(newMember);
}

void    ChatRoom::AddasMediator(std::string &NewMediator){
    this->_Mediators.push_back("@" + NewMediator);
}

bool    ChatRoom::IsInviteList(std::string& TargetUser)
{
    int i = -1;
    while (++i < _InviteList.size())
    {
        if (_InviteList.at(i) == TargetUser)
            return true;
    }
    return false;
}

bool    ChatRoom::IsBanned(std::string& IfBanned){
    int i = -1;
    while (++i < _BannedUsers.size()){
        if (_BannedUsers.at(i) == IfBanned)
            return true;
    }
    return false;
}

bool    ChatRoom::IsMediator(std::string& MayMediator){
    
    std::string Searchfor("@" + MayMediator);

    int i = -1;
    while (++i < _Mediators.size()){
        if (_Mediators.at(i) == Searchfor)
            return true;
    }
    return false;
}

bool    ChatRoom::IsalreadyMember(std::string& MayUser){
    if (IsMediator(MayUser) == true)
        return true;
    int i = -1;
    while (++i < _Members.size()){
         if (MayUser.compare(_Members.at(i)) == 0)
            return true;
    }
    return false;
}

ChatRoom::ChatRoom(){}

ChatRoom::~ChatRoom(){}

ChatRoom::ChatRoom(std::string& Creator, std::string& SetRoomName): _RoomName(SetRoomName), _ChatKey(""){
    // _Members.push_back("@" + Creator);
    _Mediators.push_back("@" + Creator);
    _AllowedUsers = 150;
    keyStatus = false;
    _Acces_isInviteOnly = false;
}

/***************************************************************************************/
typedef std::string str;

class InvalidChannelName : public std::exception{
    public :
            virtual const char* what() const throw(); 
};

const char* InvalidChannelName::what() const throw(){
    return ("");
}


bool FollowGrammar(std::string &channel)
{
    if (channel.at(0) == '#')
        return true;
    return false;
}

/***********************************/
std::vector<ChatRoom> serverglobal; //will bE static in my true implementation 

typedef std::vector<ChatRoom>::iterator VectITER;

std::string ToUpper(std::string channel)
{
    std::transform(channel.begin(), channel.end(), channel.begin(), ::toupper);
    return (channel);
}
enum    ChannelStatus{
    TOBE_JOINED = 0,
    TOBE_BUILDED,
};

enum ChannelStatus     FindInGlobalChannel(const std::string& SearchFor)
{
    VectITER iter = serverglobal.begin();

    while (iter != serverglobal.end()){
        if (ToUpper((*iter).GetRoomname()) == ToUpper(SearchFor))
            return TOBE_JOINED;
        iter++;
    }
    return TOBE_BUILDED;
}

/************************************/

std::vector<ChatRoom>::iterator FindUsingName(std::string& channelName)
{
    std::vector<ChatRoom>::iterator it = serverglobal.begin();
    while (it != serverglobal.end())
    {
        if (ToUpper((*it).GetRoomname()) == ToUpper(channelName)){
            return it ;
        }
        it++;
    }
    //Be careful With this return ... // it's ok Because To be Here th channel should be flaged 
    //as Tobejoined so it's finded ;
    return (serverglobal.end());
}

enum KeyType
{
    KEY_PROVIDED,
    NO_KEY_PROVIDED,
};

// *iter hold channel;
void    BroadcastMessage(std::string user, std::string ChannelName, std::vector<ChatRoom>::iterator& iter){
    std::map<int ,CLIENTD>::iterator GlobaLiter = ClientGlobal::ServerClients.begin();
    while (GlobaLiter !=  ClientGlobal::ServerClients.end()){
        if ((*iter).IsalreadyMember(GlobaLiter->second.nickname) == true && GlobaLiter->second.nickname != user ){
            std::string response = ":" + user + "!" + MYhost::GetHost() + " JOIN " + ChannelName + "\n";;;;;;;;;;;
                // send(GlobaLiter->first, response.c_str(), response.length(), 0);
        }
        GlobaLiter++;
    }
}

//Just to simplify the complicated things hh :
// The flag is set to separat beetwen two cases :
// @=case Where there is a channel and an equivalent password will check a lot of Condition
// @=2 try TO JOIN A CHANNEL an no Key Given so if channel require password error
    // I don't Have a Password I'll not get in Channel
    //
    /*iter Will be an iterator to channel Object*/
void    PassworMatcher(int __fd, std::vector<ChatRoom>::iterator& iter, std::string &user, \
                            std::string &ChannelName, std::string& Key, enum KeyType KeyFlag)
{
    if ((*iter).keyStatus == true){
        if ((*iter)._ChatKey.compare(Key) == 0 && KeyFlag == KEY_PROVIDED){
            std::cout << "User added bECAUSE TH KEY match"<< std::endl;
                (*iter).Addasmember(user);
                /*Send to this user in it fd self*/
                    std::string response = ":" + user + "!" + MYhost::GetHost() + " JOIN " + ChannelName + "\n";
                    response += ":" + MYhost::GetHost() + " 353 " + user + " = " + ChannelName + " " + (*iter).MembersList() + "\n";
                        response += ":" + MYhost::GetHost() + " 366 " + user + " " + ChannelName + " :End of NAMES list";
                            // send(__fd, response.c_str(), response.length(), 0);
                            BroadcastMessage(user, ChannelName, iter); //Broadcast  a new user is comming.
    }
        else{ // Send wrong password
                    std::string response = MYhost::GetHost() + " " + "475" + " " + user + " " + ChannelName + ": Wrong Channel Password (+k)";
                        // send(__fd, response.c_str(), response.length(), 0);
                    }
        }
            else{
                    (*iter).Addasmember(user);
                        std::string response = ":" + user + "!" + MYhost::GetHost() + " JOIN " + ChannelName + "\n";
                            response += ":" + MYhost::GetHost() + " 353 " + user + " = " + ChannelName + " " + (*iter).MembersList() + "\n";
                                response += ":" + MYhost::GetHost() + " 366 " + user + " " + ChannelName + " :End of NAMES list";
                                    // send(__fd, response.c_str(), response.length(), 0);
                                        BroadcastMessage(user, ChannelName, iter); //Broadcast  a new user is comming.
                        }
    //channel is not invite only so we will acces it with the key
}

void    JoinWithKey(int __fd, std::string &user, std::string &ChannelName, std::string& Key, enum KeyType KeyFlag){   
    
    //Extract the object with sameName of channel;
    std::vector<ChatRoom>::iterator iter = FindUsingName(ChannelName);

    if ((*iter).IsalreadyMember(user) == false){ // if user is current Member 
        if ((*iter).IsBanned(user) == false){ //ban or not 
            if ((*iter)._Mediators.size() + (*iter)._Members.size() < (*iter)._AllowedUsers){//channel is Full or not 
                if ((*iter)._Acces_isInviteOnly == true){    // channel +i avtived
                    if ((*iter).IsInviteList(user) == true){ // channel is invite only and User is invited also
                            (*iter).Addasmember(user);
                    std::string response = ":" + user + "!" + MYhost::GetHost() + " JOIN " + ChannelName + "\n";
                response += ":" + MYhost::GetHost() + " 353 " + user + " = " + ChannelName + " " + (*iter).MembersList() + "\n";
            response += ":" + MYhost::GetHost() + " 366 " + user + " " + ChannelName + " :End of NAMES list";
        // send(__fd, response.c_str(), response.length(), 0);
        BroadcastMessage(user, ChannelName, iter); //Broadcast  a new user is comming.
        }
        else{//1 INVITE ONLY
                    std::string response = MYhost::GetHost() + " " + "473" + " " + user + " " + ChannelName + " :Channel is Invite only (+i)" ;            
                            // send(__fd, response.c_str(), response.length(), 0);
                    }//1
        }
            else{//2 Password matching [PROVIDED, NOTPROVIDED];
                        PassworMatcher(__fd, iter, user, ChannelName, Key, KeyFlag);
                        }//2  
            }
                else{//3 Excedlimit :
                            std::string response = MYhost::GetHost() + " " + "471" + " " + user + " " + ChannelName + " :This channel exceeds limits";
                                // send(__fd, response.c_str(), response.length(), 0);
                            }// 3
                }
                    else{// 4Banned :
                                std::string response = MYhost::GetHost() + " " + "474" + " " + user + " " + ChannelName + " :You are an active ban on this channel";
                                    // send(__fd, response.c_str(), response.length(), 0);
                                }//4
                    }
                        else{ //5 alreadyMember :
                                    std::string response = MYhost::GetHost() + " " + "443" + " " + user + " " + ChannelName + " :You are already on channel";
                                        // send(__fd, response.c_str(), response.length(), 0);
                                    } //5
}

void     ExtractChannels(std::string& ClientMsg, std::vector<std::string>& Channels){
        std::stringstream channelstream(ClientMsg);
        std::string channelHolder;

        channelstream >> channelHolder;//Ignore the join command;
        channelHolder.clear();
        channelstream >> channelHolder;//GetchannelsList

        std::stringstream stream(channelHolder); /*<Give My channelList to a stream to Display it>*/
        std::string SingleChannel;

        while (std::getline(stream, SingleChannel, ',')){ //Make Vector of channels;
            Channels.push_back(SingleChannel);
        }
}

    
void    ExtractKeys(std::string& ClientMsg, std::vector<std::string>& keys)
{
        std::stringstream keystream(ClientMsg);
        std::string keyHolder;

        keystream >> keyHolder >> keyHolder ; //ignore join and channelList
        keyHolder.clear();
        keystream >>  keyHolder ; //GetKeyList;
        
        std::stringstream stream(keyHolder);
        std::string SingleKey; /*<catch every single key with this >*/

          while (std::getline(stream, SingleKey, ',')){ //Make Vector of keys;
            keys.push_back(SingleKey);
        }
}

int main (int ac, char **av)
{
    if (ac == 2){
 
        std::string clientmsg(av[1]);
        

        std::vector<std::string> Channels;
        std::vector<std::string> keys;
        ExtractChannels(clientmsg, Channels);   //makeVector of channels
        ExtractKeys(clientmsg, keys);       //MakeVector of Keys



/***********************************************************************/
    const char *STAT[]= {"TOBE_JOINED", "TOBE_BUILDED",NULL};
/***********************************************************************/
    /*OH MY COOOODE clean code as  Fuck hhhh */
        int i = -1;
        int __fd ;
        while (++i < Channels.size()){
        try{
            if (FollowGrammar(Channels.at(i))){
                if(FindInGlobalChannel(Channels.at(i)) == TOBE_BUILDED ){
                    ChatRoom BuildRoom(ClientGlobal::ServerClients.at(8).nickname, Channels.at(i));
                        std::string response = ":" + ClientGlobal::ServerClients.at(8).nickname + "!" + MYhost::GetHost() + " JOIN " + BuildRoom._RoomName + "\n";
                    response += ":" + MYhost::GetHost() + " 353 " + ClientGlobal::ServerClients.at(8).nickname + " = " + BuildRoom._RoomName + " " + BuildRoom.MembersList() + "\n";
                response += ":" + MYhost::GetHost() + " 366 " + ClientGlobal::ServerClients.at(8).nickname + " " + BuildRoom._RoomName + " :End of NAMES list";
            // send(__fd, response.c_str(), response.length(), 0);
        serverglobal.push_back(BuildRoom);//Will be changed By My GlobalSerer data attribut 
    }
    else{ // TO_BEJOINED With a key given ! Keystatus == 1(INSERT THE CODE GIVED, TRUE || False
            if (i < keys.size())
            {
                try{
                        JoinWithKey(__fd, ClientGlobal::ServerClients.at(8).nickname, Channels.at(i), keys.at(i), KEY_PROVIDED);
                }
                catch (std::exception& e){
                                std::cout << "Exception Throwed and Catched Due to Reason : ";
                                    std::cout << e.what() << std::endl;
                }
            }
            else {//a
                    try{ // Keystatus == true just back you don't have the key 
                            std::string EmptyPass("");
                                JoinWithKey(__fd ,ClientGlobal::ServerClients.at(0).nickname, Channels.at(i), EmptyPass , NO_KEY_PROVIDED);
                }
                catch(std::exception& e){
                            std::cout << "Exception Throwed and Catched Due to Reason : ";
                                std::cout << e.what() << std::endl;
                }
                                        }//!aa
    }
            }else
                throw InvalidChannelName();
        }catch (InvalidChannelName& e){
                std::string response =  MYhost::GetHost() + " 489 " +  ClientGlobal::ServerClients.at(8).nickname + " " + Channels.at(i) + " :Invalid channel name";
                    std::cout << response << std::endl;
                        e.what();    
        }
}
}
    return (0);
}