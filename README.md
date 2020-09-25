# <실전 대비 C 알고리즘 인터뷰> 

이 저장소에는 <실전 대비 C 알고리즘 인터뷰>의 소스 코드가 담겨 있습니다.

- [영문판 소스 코드](https://github.com/Hemant-Jain-Author/Problem-Solving-in-Data-Structures-and-Algorithms-using-C)에 없는 연습 문제 풀이도 담겨 있습니다.
- 장마다 예제와 해결책이 한 파일에 담겨 있습니다. 예제와 해결책 번호로 검색할 수 있습니다.
- 연습 문제 풀이는 장마다 따로 있으며 문제별로 파일이 나뉘어 있습니다.

## 소스 코드 다운로드 방법

프로젝트를 다운로드하는 방법은 두 가지입니다. 

- 프로젝트 페이지에서 ZIP 다운로드 버튼을 클릭하여 ZIP 아카이브를 다운로드한 다음 선택한 디렉터리에서 압축을 풉니다.
- 프로젝트를 수정하거나 추가할 때 쉽게 업데이트할 수 있도록 Git을 사용하여 프로젝트를 복제할 수 있습니다. 단, PC에 Git이 설치되어 있어야 합니다.

## strcpy 관련 Visaul Studio 설정

- `strcpy`는 Visual Studio에서 정상 동작하지 않습니다.
- MS는 stack overflow 공격에 대한 우려로 `strcpy_s`를 추가로 제공하며 이는 C11 표준에 추가되었지만, 필수 사항이 아니라 옵션이라 일부 유닉스쪽 컴파일러에선 동작 하지 않습니다.
- Visual Studio에서는 프로젝트 속성의 전처리기 항목에 `_CRT_SECURE_NO_WARNINGS`를 추가하면 해결됩니다. 
- [_CRT_SECURE_NO_WARNINGS](https://github.com/gilbutITbook/007031/blob/master/_CRT_SECURE_NO_WARNINGS.png)를 참조하세요.

