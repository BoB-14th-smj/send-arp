# 영상
[유튜브 영상 링크](https://www.youtube.com/watch?v=GT6TtJke1vo)

## 실험 설명
- 1. BROADCAST로 sender 의 MAC 주소를 받아온다(이때, 나의 IP주소 필요)
- 2. SENDER 의 ARP 테이블에서 Target 의 MAC주소를 내걸로 보내는 REPLY를 보낸다.
- 3. 결과값을 확인한다.
 

# 영상 설명
- 성밍쟁 앙잉퐁 172.20.10.1 핫스팟에 호스트PC 172.20.10.2, GUEST(VM) 172.20.10.5 의 각 MAC주소를 알아내고 메모장에 적는다
- GUEST에서 Host의 ARP 테이블에서 게이트웨이의 MAC주소를 변조한다.
- 호스트에서 arp -a 로 변조된 것을 확인한다
- 호스트에서 ping 을 날렸을 때, 게스트 wireshark 로 잡히는지 확인한다.
  



# Reference
### EXIT_FAILURE & EXIT_SUCCESS
- https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/exit-success-exit-failure?view=msvc-170

### struct vs class
- https://pandas-are-bears.tistory.com/13


### arp header
- https://en.wikipedia.org/wiki/Address_Resolution_Protocol
- https://kitribob.wiki/wiki/ARP


### get MAC Address
- https://yogyui.tistory.com/entry/CLinux%EC%97%90%EC%84%9C-%EB%84%A4%ED%8A%B8%EC%9B%8C%ED%81%AC-%EC%96%B4%EB%8C%91%ED%84%B0-MAC-Address-%EA%B0%80%EC%A0%B8%EC%98%A4%EA%B8%B0
- https://py0zz1.tistory.com/entry/ARP-Spoofing-Tool-%EC%9E%90%EB%8F%99%ED%99%94-%EC%97%85%EB%8D%B0%EC%9D%B4%ED%8A%B8-%EC%BD%94%EB%93%9C-%EB%B3%B4%EC%99%84
- https://youonlyliveonce1.tistory.com/51


### segmentfault
- https://codingfriend.tistory.com/18


### find ip in linux
- https://bono915.tistory.com/entry/Linux-%EB%A6%AC%EB%88%85%EC%8A%A4-IP-%ED%99%95%EC%9D%B8-%EB%B0%A9%EB%B2%95

### string find
- https://roadtosuccess.tistory.com/82

### constructor
- https://boycoding.tistory.com/244


### stoi
- https://dream-and-develop.tistory.com/57
- https://blockdmask.tistory.com/333


### enum
- https://dragondeok.tistory.com/44
- https://gitlab.com/gilgil/send-arp-test/-/blob/master/src/arphdr.h?ref_type=heads


### sendpacket
- https://www.sapphosound.com/archives/1923

### delete padding
- https://park-duck.tistory.com/entry/CCC-%EA%B5%AC%EC%A1%B0%EC%B2%B4-padding-%EC%A0%9C%EA%B1%B0feat-%EA%B5%AC%EC%A1%B0%EC%B2%B4-%ED%81%AC%EA%B8%B0-%EA%B3%84%EC%82%B0


### Initial List (GPT)
- ArpPacket(Ethernet* ethernet_, Arp* arp_) : ethernet(*ethernet_), arp(*arp_){};
- https://pandas-are-bears.tistory.com/16
- https://blockdmask.tistory.com/510
