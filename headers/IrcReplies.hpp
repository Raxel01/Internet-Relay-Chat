/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcReplies.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:53:47 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/06 13:53:48 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define RPL_WELCOME "001"
#define RPL_YOURHOST "002"
#define RPL_CREATED "003"
#define RPL_MYINFO "004"
#define RPL_BOUNCE "005"
#define RPL_USERHOST "302"
#define RPL_ISON "303"
#define RPL_AWAY "301"
#define RPL_UNAWAY "305"
#define RPL_NOWAWAY "306"
#define RPL_WHOISUSER "311"
#define RPL_WHOISSERVER "312"
#define RPL_WHOISOPERATOR "313"
#define RPL_WHOISIDLE "317"
#define RPL_ENDOFWHOIS "318"
#define RPL_WHOISCHANNELS "319"
#define RPL_WHOWASUSER "314"
#define RPL_ENDOFWHOWAS "369"
#define RPL_LISTSTART "321"
#define RPL_LIST "322"
#define RPL_LISTEND "323"
#define RPL_UNIQOPIS "325"
#define RPL_CHANNELMODEIS "324"
#define RPL_NOTOPIC "331"
#define ERR_INVALIDMODEPARAM "696"
#define RPL_TOPIC "332"
#define RPL_INVITING "341"
#define RPL_SUMMONING "342"
#define RPL_INVITELIST "346"
#define RPL_ENDOFINVITELIST "347"
#define RPL_EXCEPTLIST "348"
#define RPL_ENDOFEXCEPTLIST "349"
#define RPL_VERSION "351"
#define RPL_WHOREPLY "352"
#define RPL_ENDOFWHO "315"
#define RPL_NAMREPLY "353"
#define RPL_ENDOFNAMES "366"
#define RPL_LINKS "364"
#define RPL_ENDOFLINKS "365"
#define RPL_BANLIST "367"
#define RPL_ENDOFBANLIST "368"
#define RPL_INFO "371"
#define RPL_ENDOFINFO "374"
#define RPL_MOTDSTART "375"
#define RPL_MOTD "372"
#define RPL_ENDOFMOTD "376"
#define RPL_YOUREOPER "381"
#define RPL_REHASHING "382"
#define RPL_YOURESERVICE "383"
#define RPL_TIME "391"
#define RPL_USERSSTART "392"
#define RPL_USERS "393"
#define RPL_ENDOFUSERS "394"
#define RPL_NOUSERS "395"
#define ERR_NOSUCHNICK "401"
#define ERR_NOSUCHSERVER "402"
#define ERR_NOSUCHCHANNEL "403"
#define ERR_CANNOTSENDTOCHAN "404"
#define ERR_TOOMANYCHANNELS "405"
#define ERR_WASNOSUCHNICK "406"
#define ERR_TOOMANYTARGETS "407"
#define ERR_NOSUCHSERVICE "408"
#define ERR_NOORIGIN "409"
#define ERR_NORECIPIENT "411"
#define ERR_NOTEXTTOSEND "412"
#define ERR_NOTOPLEVEL "413"
#define ERR_WILDTOPLEVEL "414"
#define ERR_BADMASK "415"
#define ERR_UNKNOWNCOMMAND "421"
#define ERR_NOMOTD "422"
#define ERR_NOADMININFO "423"
#define ERR_FILEERROR "424"
#define ERR_NONICKNAMEGIVEN "431"
#define ERR_ERRONEUSNICKNAME "432"
#define ERR_NICKNAMEINUSE "433"
#define ERR_NICKCOLLISION "436"
#define ERR_UNAVAILRESOURCE "437"
#define ERR_USERNOTINCHANNEL "441"
#define ERR_NOTONCHANNEL "442"
#define ERR_USERONCHANNEL "443"
#define ERR_NOLOGIN "444"
#define ERR_SUMMONDISABLED "445"
#define ERR_USERSDISABLED "446"
#define ERR_NOTREGISTERED "451"
#define ERR_NEEDMOREPARAMS "461"
#define ERR_ALREADYREGISTRED "462"
#define ERR_NOPERMFORHOST "463"
#define ERR_PASSWDMISMATCH "464"
#define ERR_YOUREBANNEDCREEP "465"
#define ERR_YOUWILLBEBANNED "466"
#define ERR_KEYSET "467"
#define ERR_CHANNELISFULL "471"
#define ERR_UNKNOWNMODE "472"
#define ERR_INVITEONLYCHAN "473"
#define ERR_BANNEDFROMCHAN "474"
#define ERR_BADCHANNELKEY "475"
#define ERR_BADCHANMASK "476"
#define ERR_NOCHANMODES "477"
#define ERR_BANLISTFULL "478"
#define ERR_NOPRIVILEGES "481"
#define ERR_CHANOPRIVSNEEDED "482"
#define ERR_CANTKILLSERVER "483"
#define ERR_RESTRICTED "484"
#define ERR_UNIQOPPRIVSNEEDED "485"
#define ERR_NOOPERHOST "491"
#define ERR_UMODEUNKNOWNFLAG "501"
#define ERR_USERSDONTMATCH "502"


#define RPL_SERVICEINFO "231"
#define RPL_ENDOFSERVICES "232"
#define RPL_SERVICE "233"
#define RPL_SERVLIST "234"
#define RPL_SERVLISTEND "235"
#define RPL_WHOISCHANOP "316"
#define RPL_KILLDONE "361"
#define RPL_CLOSING "362"
#define RPL_CLOSEEND "363"
#define RPL_INFOSTART "373"
#define RPL_MYPORTIS "384"
#define RPL_STATSCLINE "213"
#define RPL_STATSNLINE "214"
#define RPL_STATSILINE "215"
#define RPL_STATSKLINE "216"
#define RPL_STATSQLINE "217"
#define RPL_STATSYLINE "218"
#define RPL_STATSVLINE "240"
#define RPL_STATSLLINE "241"
#define RPL_STATSHLINE "244"
#define RPL_STATSPING "246"
#define RPL_STATSBLINE "247"
#define RPL_STATSDLINE "250"
#define RPL_LUSERCLIENT "251"
#define RPL_LUSEROP "252"
#define RPL_LUSERUNKNOWN "253"
#define RPL_LUSERCHANNELS "254"
#define RPL_LUSERME "255"
#define RPL_ADMINME "256"
#define RPL_ADMINLOC1 "257"
#define RPL_ADMINLOC2 "258"
#define RPL_ADMINEMAIL "259"
#define RPL_TRYAGAIN "263"
#define RPL_LOCALUSERS "265"
#define RPL_GLOBALUSERS "266"
#define RPL_START_NETSTAT "267"
#define RPL_NETSTAT "268"
#define RPL_END_NETSTAT "269"
#define RPL_PRIVS "270"
#define RPL_SILELIST "271"
#define RPL_ENDOFSILELIST "272"
#define RPL_NOTIFY "273"
#define RPL_ENDNOTIFY "274"
#define RPL_STATSDELTA "274"
#define RPL_WHOISCERTFP "276"
#define RPL_VCHANEXIST "277"
#define RPL_VCHANLIST "278"
#define RPL_VCHANHELP "280"
#define RPL_GLIST "280"
#define RPL_CHANINFO_KICKS "296"
#define RPL_END_CHANINFO "299"
#define RPL_NONE "300"
#define RPL_AWAY "301"
#define RPL_USERHOST "302"
#define RPL_ISON "303"
#define RPL_TEXT "304"
#define RPL_UNAWAY "305"
#define RPL_NOWAWAY "306"
#define RPL_WHOISREGNICK "307"
#define RPL_RULESSTART "308"
#define RPL_ENDOFRULES "309"
#define RPL_WHOISADMIN "310"
#define RPL_WHOISSADMIN "309"
#define RPL_WHOISHELPER "309"
#define RPL_WHOISSVCMSG "309"
#define RPL_WHOISHELPOP "309"
#define RPL_WHOISUSER "311"
#define RPL_WHOISSERVER "312"
#define RPL_WHOISOPERATOR "313"
#define RPL_WHOWASUSER "314"
#define RPL_ENDOFWHO "315"
#define RPL_WHOISCHANREG "316"
#define RPL_WHOISIDLE "317"
#define RPL_ENDOFWHOIS "318"
#define RPL_WHOISCHANNELS "319"
#define RPL_WHOISSPECIAL "320"
#define RPL_LISTSTART "321"
#define RPL_LIST "322"
#define RPL_LISTEND "323"
#define RPL_CHANNELMODEIS "324"
#define RPL_UNIQOPIS "325"
#define RPL_CHANNELPASSIS "325"
#define RPL_NOCHANPASS "326"
#define RPL_CHPASSUNKNOWN "327"
#define RPL_CHANNEL_URL "328"
#define RPL_CREATIONTIME "329"
#define RPL_WHOWAS_TIME "330"
#define RPL_WHOISACCOUNT "330"
#define RPL_NOTOPIC "331"
#define RPL_TOPIC "332"
#define RPL_TOPICWHOTIME "333"
#define RPL_LISTUSAGE "334"
#define RPL_COMMANDSYNTAX "334"
#define RPL_LISTSYNTAX "334"
#define RPL_CHANPASSOK "338"
#define RPL_BADCHANPASS "339"
#define RPL_INVITING "341"
#define RPL_SUMMONING "342"
#define RPL_INVITELIST "346"
#define RPL_ENDOFINVITELIST "347"
#define RPL_EXCEPTLIST "348"
#define RPL_ENDOFEXCEPTLIST "349"
#define RPL_VERSION "351"
#define RPL_WHOREPLY "352"
#define RPL_NAMREPLY "353"
#define RPL_WHOSPCRPL "354"
#define RPL_NAMREPLY_ "355"
#define RPL_MAP "357"
#define RPL_MAPMORE "358"
#define RPL_MAPEND "359"
#define RPL_KILLDONE "361"
#define RPL_CLOSING "362"
#define RPL_CLOSEEND "363"
#define RPL_LINKS "364"
#define RPL_ENDOFLINKS "365"
#define RPL_ENDOFNAMES "366"
#define RPL_BANLIST "367"
#define RPL_ENDOFBANLIST "368"
#define RPL_ENDOFWHOWAS "369"
#define RPL_INFO "371"
#define RPL_MOTD "372"
#define RPL_INFOSTART "373"
#define RPL_ENDOFINFO "374"
#define RPL_MOTDSTART "375"
#define RPL_ENDOFMOTD "376"
#define RPL_WHOISHOST "378"
#define RPL_WHOISMODES "379"
#define RPL_YOUREOPER "381"
#define RPL_REHASHING "382"
#define RPL_YOURESERVICE "383"
#define RPL_MYPORTIS "384"
#define RPL_NOTOPERANYMORE "385"
#define RPL_QLIST "386"
#define RPL_ENDOFQLIST "387"
#define RPL_ALIST "388"
#define RPL_ENDOFALIST "389"
#define RPL_TIME "391"

#define ERR_NOSUCHNICK "401"
#define ERR_NOSUCHSERVER "402"
#define ERR_NOSUCHCHANNEL "403"
#define ERR_CANNOTSENDTOCHAN "404"
#define ERR_TOOMANYCHANNELS "405"
#define ERR_WASNOSUCHNICK "406"
#define ERR_TOOMANYTARGETS "407"
#define ERR_NOSUCHSERVICE "408"
#define ERR_NOORIGIN "409"
#define ERR_NORECIPIENT "411"
#define ERR_NOTEXTTOSEND "412"
#define ERR_NOTOPLEVEL "413"
#define ERR_WILDTOPLEVEL "414"
#define ERR_BADMASK "415"
#define ERR_UNKNOWNCOMMAND "421"
#define ERR_NOMOTD "422"
#define ERR_NOADMININFO "423"
#define ERR_FILEERROR "424"
#define ERR_NOOPERMOTD "425"
#define ERR_TOOMANYAWAY "429"
#define ERR_EVENTNICKCHANGE "430"
#define ERR_NONICKNAMEGIVEN "431"
#define ERR_ERRONEUSNICKNAME "432"
#define ERR_NICKNAMEINUSE "433"
#define ERR_NICKCOLLISION "436"
#define ERR_UNAVAILRESOURCE "437"
#define ERR_EVENTBANCHANGE "439"
#define ERR_NICKTOOFAST "438"
#define ERR_TARGETTOOFAST "439"
#define ERR_SERVICESDOWN "440"
#define ERR_USERNOTINCHANNEL "441"
#define ERR_NOTONCHANNEL "442"
#define ERR_USERONCHANNEL "443"
#define ERR_NOLOGIN "444"
#define ERR_SUMMONDISABLED "445"
#define ERR_USERSDISABLED "446"
#define ERR_NONICKCHANGE "447"
#define ERR_EVENTDELCREATION "448"
#define ERR_EVENTDELBAN "449"
#define ERR_EVENTDELINVITE "450"
#define ERR_EVENTDELEVENT "451"
#define ERR_NOTREGISTERED "451"
#define ERR_NEEDMOREPARAMS "461"
#define ERR_ALREADYREGISTRED "462"
#define ERR_NOPERMFORHOST "463"
#define ERR_PASSWDMISMATCH "464"
#define ERR_YOUREBANNEDCREEP "465"
#define ERR_YOUWILLBEBANNED "466"
#define ERR_KEYSET "467"
#define ERR_INVALIDUSERNAME "468"
#define ERR_LINKSET "469"
#define ERR_LINKCHANNEL "470"
#define ERR_CHANNELISFULL "471"
#define ERR_UNKNOWNMODE "472"
#define ERR_INVITEONLYCHAN "473"
#define ERR_BANNEDFROMCHAN "474"
#define ERR_BADCHANNELKEY "475"
#define ERR_BADCHANMASK "476"
#define ERR_NEEDREGGEDNICK "477"
#define ERR_BANLISTFULL "478"
#define ERR_BADCHANNAME "479"
#define ERR_LINKFAIL "479"
#define ERR_NOPRIVILEGES "481"
#define ERR_CHANOPRIVSNEEDED "482"
#define ERR_CANTKILLSERVER "483"
#define ERR_ISCHANSERVICE "484"
#define ERR_BANNEDNICK "485"
#define ERR_NONONREG "486"
#define ERR_HTMDISABLED "487"
#define ERR_EVENTNICKINUSE "488"
#define ERR_NONICKCHANGE_ "488"
#define ERR_VOICENEEDED "489"
#define ERR_NOOPERHOST "491"
#define ERR_NOSERVICEHOST "492"
#define ERR_NOFEATURE "493"
#define ERR_BADFEATURE "494"
#define ERR_BADLOGTYPE "495"
#define ERR_BADLOGSYS "496"
#define ERR_BADLOGVALUE "497"
#define ERR_ISOPERLCHAN "498"
#define ERR_CHANOWNPRIVNEEDED "499"
#define ERR_UMODEUNKNOWNFLAG "501"
#define ERR_USERSDONTMATCH "502"
#define ERR_GHOSTEDCLIENT "503"
#define ERR_USERNOTONSERV "504"
#define ERR_SILELISTFULL "511"
#define ERR_TOOMANYWATCH "512"
#define ERR_BADPING "513"
#define ERR_INVALID_ERROR "514"
#define ERR_TOOMANYDCC "514"
#define ERR_BADEXPIRE "515"
#define ERR_DONTCHEAT "516"
#define ERR_DISABLED "517"
#define ERR_NOINVITE "518"
#define ERR_LONGMASK "518"
#define ERR_ADMONLY "519"
#define ERR_TOOMANYUSERS "519"
#define ERR_OPERONLY "520"
#define ERR_MASKTOOWIDE "520"
#define ERR_WHOTRUNC "520"
#define ERR_LISTSYNTAX "521"
#define ERR_WHOSYNTAX "522"
#define ERR_WHOLIMEXCEED "523"
#define ERR_QUARANTINED "524"
#define ERR_OPERSPVERIFY "524"
#define ERR_REMOTEPFX "525"
#define ERR_PFXUNROUTABLE "526"
#define ERR_BADHOSTMASK "550"
#define ERR_HOSTUNAVAIL "551"
#define ERR_USINGSLINE "552"
#define ERR_STATSSLINE "553"
#define ERR_NOTALLOWED "554"
#define ERR_HOSTILENAME "555"
#define ERR_NOHIDING "556"
#define ERR_NOTFORHALFOPS "557"
#define ERR_NEEDMOREPARAMS_ "558"
#define ERR_ALREADYREGISTERED "559"




#define MODIFIEABLE_TOPIC 1
#define UNMODIFIEABLE_TOPIC 0