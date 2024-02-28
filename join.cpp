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
// #include <pair>

class MYhost
{
    public :
    static std::string GetHost(){
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
};

/*CHANNEEEEEL OPERATIONS AND CLASS******************************************************/
typedef std::deque<std::string> DEQUE ;

class CLIENTD{
    public :
        std::string nickname;
        std::string username;
        std::string ipAddress;
        CLIENTD(std::string Setnickname, std::string Setusername, std::string Setip);
};

class ClientGlobal
{
    public :
        static std::map<int, CLIENTD> ServerClients;
};

std::map<int, CLIENTD> ClientGlobal::ServerClients;

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
        size_t               UsersCounter       ; //How Many users JOINED THE CHANNEL
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
        void            getelems(){
            DEQUE::iterator it = _Mediators.begin();
            
            while (it != _Mediators.end()){
                std::cout << "Mediator : " << *it<< std::endl;
                it++;
            }

            it = _Members.begin();
            while (it != _Members.end()){
                std::cout << "mEMBER : " << *it<< std::endl;
                it++;
            }
            std::cout << "^^^^^^^^^^^Members^^^^^^^^^" << std::endl;
            std::cout << "RoomNAME => " << _RoomName << std::endl;

            std::cout << "Keysstatus : " << keyStatus << std::endl;  
            std::cout << "Users Joined Channel " << UsersCounter << std::endl;
            std::cout << "________________________________________________"<< std::endl;
        }
        
        const std::string&    GetRoomname(){
    return _RoomName;
}    
        ~ChatRoom(); 
};

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
         if (MayUser.compare(_Members.at(i))== 0)
            return true;
    }
    return false;
}

ChatRoom::ChatRoom(){}

ChatRoom::~ChatRoom(){}

ChatRoom::ChatRoom(std::string& Creator, std::string& SetRoomName): _RoomName(SetRoomName), UsersCounter(0), _ChatKey(""){
    // _Members.push_back("@" + Creator);
    _Mediators.push_back("@" + Creator);
    _AllowedUsers = 150;
    keyStatus = false;
    UsersCounter++;
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
std::vector<ChatRoom> serverglobal;


enum    ChannelStatus{
    TOBE_JOINED = 0,
    TOBE_BUILDED,
};

typedef std::vector<ChatRoom>::iterator VectITER;

std::string ToUpper(std::string channel)
{
    std::transform(channel.begin(), channel.end(), channel.begin(), ::toupper);
    return (channel);
}

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
//Just to simplify the complicated things hh :
// The flag is set to separat beetwen to cases :
// @=case Where there is a channel and an equivalent password will check a lot of Condition
// @=2 try TO JOIN A CHANNEL an no Key Given so if channel require password error
    // I don't Have a Password I'll not get in Channel
    //
void    JoinWithKey(std::string &user, std::string &ChannelName, std::string& Key, enum KeyType KeyFlag){   
    //Extract the object with sameName of channel;
    std::vector<ChatRoom>::iterator iter = FindUsingName(ChannelName);

    
    user = "BOLALAn";
    (*iter).AddasMediator(user);
    // (*iter).keyStatus = true;
    // (*iter)._ChatKey = "Fortan";
    // (*iter).AddasMediator(user);
    // (*iter)._ChatKey="GOOD";
    // (*iter)._BannedUsers.push_back(user);
    // (*iter)._AllowedUsers = 1;
    // (*iter).keyStatus = 1;
    (*iter)._Acces_isInviteOnly = true;
    (*iter)._InviteList.push_back(user);
    if ((*iter).IsalreadyMember(user) == false){  // std::cout << " notttt IN CHANNEL " << std::endl;
        if ((*iter).IsBanned(user) == false){ //check if user is banned or not 
            if ((*iter)._Mediators.size() + (*iter)._Members.size() < (*iter)._AllowedUsers){    //check if the Limit User is not arrived
                if ((*iter)._Acces_isInviteOnly == true){         // channel not Full may use memeber.size() + mediator.size();
                    if ((*iter).IsInviteList(user) == true){ // The channel is invite only and User is invited also
                            (*iter).Addasmember(user);
                            std::cout << "User Added "<< std::endl;
                            std::string response = ":" + user + "!" + MYhost::GetHost() + " JOIN " + ChannelName + "\n";
                            response += ":" + MYhost::GetHost() + " 353 " + user + " = " + ChannelName + " " + (*iter).MembersList() + "\n";
                            response += ":" + MYhost::GetHost() + " 366 " + user + " " + ChannelName + " :End of NAMES list";
                            std::cout << response << std::endl;
                            /*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                                @: Send attachmaat to him Selllfff join wlist w endof 9wada
                            */

                            //Send Message to all users in the Channel informing them That the a new user is comming.
                    }
                    else{
                        std::string response = MYhost::GetHost() + " " + "473" + " " + user + " " + ChannelName + " :Channel is Invite only (+i)" ;
                            std::cout << response << std::endl;
                            // The channel is invite only and the User is not invited
                            //  ERR_INVITEONLYCHAN (473) 
                    }
                }
                else{
                    if ((*iter).keyStatus == true){
                        if ((*iter)._ChatKey.compare(Key) == 0 && KeyFlag == KEY_PROVIDED){
                            std::cout << "User added bECAUSE TH KEY match"<< std::endl;
                                (*iter).Addasmember(user);
                                /*Send to this user in it fd self*/
                                   std::string response = ":" + user + "!" + MYhost::GetHost() + " JOIN " + ChannelName + "\n";
                            response += ":" + MYhost::GetHost() + " 353 " + user + " = " + ChannelName + " " + (*iter).MembersList() + "\n";
                            response += ":" + MYhost::GetHost() + " 366 " + user + " " + ChannelName + " :End of NAMES list";
                            std::cout << response << std::endl;
                                /**/
                            //Send Message to all users in the Channel informing them That the a new user is comming.
                            // :ornal!~u@qk3i8byd6tfyg.irc JOIN #torssan this Message To all channel member
                    }else{
                            // Send wrong password
                            //  ERR_BADCHANNELKEY (475) in his FD
                            std::string response = MYhost::GetHost() + " " + "475" + " " + user + " " + ChannelName + ": Wrong Channel Password (+k)";
                            std::cout << response << std::endl;
                    }
                } else{
                            (*iter).Addasmember(user);
                            std::string response = ":" + user + "!" + MYhost::GetHost() + " JOIN " + ChannelName + "\n";
                            response += ":" + MYhost::GetHost() + " 353 " + user + " = " + ChannelName + " " + (*iter).MembersList() + "\n";
                            response += ":" + MYhost::GetHost() + " 366 " + user + " " + ChannelName + " :End of NAMES list";
                            std::cout << response << std::endl;
                        std::cout << "Join Because no password required" << std::endl;
                            //Send Message to all users in the Channel informing them That the a new user is comming.
                    }
                //channel is not invite only so we will acces it with the key
            }  
            }else{
                // Send Error 
                // channel is Full÷    "<client> <channel> :Cannot join channel (+l)"
                // 471
                std::string response = MYhost::GetHost() + " " + "471" + " " + user + " " + ChannelName + " :This channel exceeds limits";
                std::cout << response << std::endl;
            }
        }
        else{ //Banned ;
            std::string response = MYhost::GetHost() + " " + "474" + " " + user + " " + ChannelName + " :You are an active ban on this channel";
            std::cout << response << std::endl;
        }
    }
    else{
        //Use Send Here the User already Exist
        std::string response = MYhost::GetHost() + " " + "443" + " " + user + " " + ChannelName + " :You are already on channel";
        std::cout << response << std::endl;
    }
}
// for the host it will be in the the Server Claas
// The I'll make a static Function That Return it bu taking this host by params 
// static GetHost(get_host())
// {
    // return (Thestring);
// }
int main (int ac, char **av)
{
    if (ac == 2){
        ClientGlobal::ServerClients.insert(std::pair<int , CLIENTD>(8, CLIENTD("canis.lupus", "Abdelali", "127.0.0.1")));
        // std::cout << ClientGlobal::ServerClients.at(8).nickname << std::endl;
        // std::cout << ClientGlobal::ServerClients.at(8).ipAddress << std::endl;
        // std::cout << ClientGlobal::ServerClients.at(8).username << std::endl;

        std::stringstream stream(av[1]);

        std::string Listofchannels;
        
        std::string ListofKeys;

        std::string catcher;

        stream >> catcher; // ignore join cmd 'JOIN'

        stream >> Listofchannels;//listofchannelsname

        std::stringstream channelstream(Listofchannels);
        
        stream >> ListofKeys;//channelskeys
        std::stringstream keystream(ListofKeys);

        std::string channelHolder;
        
        std::string keyHolder;
        std::vector<std::string> Channels;
        std::vector<std::string> keys;

        while (std::getline(channelstream, channelHolder, ',')){ //Make Vector of channels;
            Channels.push_back(channelHolder);
        }
         while (std::getline(keystream, keyHolder, ',')){ //Make Vector of keys;
            keys.push_back(keyHolder);
        }
    /********/
    const char *STAT[]= {"TOBE_JOINED", "TOBE_BUILDED",NULL};
    /**************/
    /*OH MY COOOODE clean code as  Fuck hhhh */
        int i = -1;
        std::string flanToBeadd("NEWADDED");

        std::string owner("Abdelali iat talb");
        while (++i < Channels.size()){
        try{
            if (FollowGrammar(Channels.at(i))){
                if(FindInGlobalChannel(Channels.at(i)) == TOBE_BUILDED ){
                    std::cout << "TOBEBUILDED" << std::endl;
                    ChatRoom BuildRoom(ClientGlobal::ServerClients.at(8).nickname, Channels.at(i));
                    serverglobal.push_back(BuildRoom);
                }
                else{ // TO_BEJOINED With a key given !
                    if (i < keys.size()){
                        std::cout << " TO JOIN With Key : " << keys.at(i)<< std::endl;
                        try{
                        JoinWithKey(ClientGlobal::ServerClients.at(8).nickname, Channels.at(i), keys.at(i), KEY_PROVIDED);
                        }// Search if the CHANNEL IS WITH Code if YES(keypass == TRUE, INSERT THE CODE GIVED ELSE)
                        catch (std::exception& e){
                            std::cout << "Exception Throwed and Catched Due to Reason : ";
                            std::cout << e.what() << std::endl;
                        }
                }
                else
                try{
                    std::cout << "No Key Provided : Key : " <<  i << " "<< keys.size() << std::endl;
                    std::string EmptyPass("");
                    JoinWithKey(ClientGlobal::ServerClients.at(8).nickname, Channels.at(i), EmptyPass , NO_KEY_PROVIDED);
                    //just try to be a member of this channel;
                    // if channel have code just back you don't have the Code 
                }
                catch(std::exception& e){

                }
                }
            }
            else
                throw InvalidChannelName();
        }catch (InvalidChannelName& e){
            std::string response =  MYhost::GetHost() + " 489 " +  ClientGlobal::ServerClients.at(8).nickname + " " + Channels.at(i) + " :Invalid channel name";
            std::cout << response << std::endl;
            e.what();    
        }
        }
        std::cout << "============================= Show Server Channels ========================"<< std::endl;
        std::vector<ChatRoom>::iterator it = serverglobal.begin();
        while (it != serverglobal.end()){
            std::cout << (*it).MembersList() << std::endl;
            it++;
        }
    }
    return (0);
}