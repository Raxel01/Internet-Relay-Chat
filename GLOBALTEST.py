/**********************************************************/
*
*   ALL TEST TO CHECK 
*
************************************************************

************
    join   |
************

 Space = 0 just JOIN CMD;
    * bad channel name without #
    * Join channel that exist and other to build
    * TRY to join with a key given!
    * try to join without key but channel may need key !
    * join channel where you are already member
    * join channel where you are banned
    * join channel where limit of users exceeds
    * join an invited only channel and your are not invited;
    *join and youare invited;
    { VERIFY REPLIES SHOULD BE THE SAME AS IRC |REFERENCE }
     _________________
----|  MODE           |
    |___________|------

    MODE only => no enough params

    GetChannel Mode by : MODE  #channel
    check the validity of the channel : 
    *wrong channel name
    non existing one
    a channel where you are not a member.
    channel where you part
    a channel where you are kicked from;
    a channel where you are invited before joining it;
    * bad mode without +/-;
    * duplicat true flags;
    * wrong flags and duplicates
    * nosuchchannel throw;
    * 1 space == getmode;
    * non mediator try to set mode;
    * test ADD MODE;
        +wrong good params only bad flags
        * args no args
        typeD i | t ;
        |- i for already invite only channel;
        |- i for non invite channel;
        |- t for builded channel and go check for topic setting;
        | -t and try to change canel TOPIC by regular user
        type B for o add; no params and with;
        TYPE C :
               * key +k for already channel with key should update the key
               * Wrong +l -l parameter limits 



