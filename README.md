남궁식 게임 클라이언트 개발자 API 포트폴리오

-에디터 : Microsoft Visual Studio Community 2019

-제작기간 : 2024-04-10 ~ 2024.05.04(약 한달)

-개발규모 : 1인 개발

플레이 동영상

https://youtu.be/GJZ8zpUlOcY

간단한 프로젝트 설명

RPG의 기본적인 움직임과 공격 및 스킬등을 구현했다.
적 AI를 통해 적의 움직임 및 공격을 구현했다.

활용 기술
- 플레이어 움직임과 공격등을 sprite 장면마다 자연스러운 애니메이션 구성을 위해 넣어 주었다.
![image](https://github.com/Namkungsik/Assassination-Of-Shogun/assets/83630680/02a93ba2-3a1c-44be-9bd0-1d282ec6abdd)

- 예를 들어 프레임마다 플레이어 애니메이션을 재생시켜서 다 재생 시켰다면 처음으로 돌아가 특정 입력을 받기전까지 재생시킨다.
  ![image](https://github.com/Namkungsik/Assassination-Of-Shogun/assets/83630680/f528fecb-33d8-414d-ae5d-40285c495f0d)

  *보스 움직임과 공격 또한 똑같이 만들었다.

  - 단, 보스는 플레이어가 직접 입력을 할 수 없기 때문에 AI로 대체했다.
 
    ![image](https://github.com/Namkungsik/Assassination-Of-Shogun/assets/83630680/2b2e9297-5ab2-463b-9b9f-ccdbbf528126)

  - 플레이어를 감지하는 범위와 공격 범위를 만들고, 그 안에 플레이어를 나타내는 Sprite가 들어오면 적의 애니메이션을 재생시킨다.

ex) 플레이어가 적의 공격범위에 들어왔을 경우 
![image](https://github.com/Namkungsik/Assassination-Of-Shogun/assets/83630680/f3c10186-d6c9-40b9-b718-fc86dc622af3)


* 리소스는 The Sprite Resource 사이트를 이용해서 제작했습니다.
