# CodeEditor
📝 CodeEditor is a text or code editor that replaces Notepad and has the ability to freely edit C ++ and C languages.

#### 프로그램 정보

**CodeEditor**는 문서 또는 코드 편집기로서, 메모장을 대신할 뿐 아니라 C++, C언어를 자유롭게 편집 가능한 기능을 가진 프로그램입니다.

##### 개발환경

| 프로그램 이름 | Code Editor Project |
| ------------- | ------------------- |
| Language      | C++, MFC            |
| 개발 도구     | Visual Studio 2015  |
| 소스코드 관리 | Git                 |
| 지원 OS       | Window 10 이상      |

​	그림1. 개발 문서

<img src="https://tva1.sinaimg.cn/large/008vOhrAgy1hd50eg20pfj30o30t4dje.jpg" style="zoom:20%;">

#### User Interface

- 메뉴선택 현재 창의 정보와 메뉴, 현재 입력되고 있는 화면과 입력 문자의 줄 번호 표시, 현재 줄의 위치를 표시한다.



​	그림2. 프로그램 시작화면

<img src="https://tva1.sinaimg.cn/large/008vOhrAgy1hd4zzcu8r6j30pm0r2myf.jpg" style="zoom:20%;">



### 상세 메뉴 기능 

1. 파일

   - 새 파일 문서를 새로 작성합니다.
   -  열기 기존 문서를 엽니다.
   - 저장 현재 열린 문서를 저장합니다.
   - 다른 이름으로 저장 새 이름으로 현재 열린 문서를 다른 이름으로 저장합니다. 
   - 끝내기 프로그램을 종료하기 위해 문서를 저장할 것인지 묻습니다.

   

2. 편집

   - 실행 취소 마지막으로 한 동작을 취소합니다.
   - 재실행 이전에 취소한 동작을 다시 수행합니다.
   - 잘라내기 선택 부분을 잘라내어 클립보드에 넣습니다. 
   - 복사 선택 부분을 복사하여 클립보드에 넣습니다 붙여넣기 클립보드의 내용을 붙여 넣습니다.
   - 삭제 선택 부분을 삭제합니다.
   - 찾기 지정한 문자열을 찾습니다.
   - 다음 찾기 다음 일치하는 말을 찾습니다.
   - 바꾸기 지정한 문자열을 다른 문자열로 바꿉니다.
   - 이동 입력한 줄로 이동합니다.
   - 모두선택 입력 된 모든 문자가 선택됩니다.
   - 시간/날짜 현재 날짜와 시간이 지정된 위치에 삽입됩니다.

3. 서식

   - 글꼴 기본 설정을 변경가능한 대화상자가 나타납니다.

4. 보기

   - 상태표시줄 현재 입력중인 문자의 줄/칸의 수를 보여줍니다.

5. 도움말

   - 도움말 보기 프로그램의 도움말 창을 띄웁니다.
   - 프로그램 정보 프로그램의 정보 창을 띄웁니다.

6. 그 외의 기능

   1. 구문 강조 기능

      C, C++ 언어에서 자주 쓰이는 구문은 각 syntax와 동일한 강조 기능을 사용할 수 있습니다.

      <img src="https://tva1.sinaimg.cn/large/008vOhrAgy1hd5087p2lmj30su0nudjv.jpg" style="zoom:50%;">

   2. 줄 번호

      줄 번호 기능을 사용하여 문서나 프로그램 소스 위치를 파악할 수 있습니다.

      <img src="https://tva1.sinaimg.cn/large/008vOhrAgy1hd5089ztlxj31hq0os7b5.jpg" style="zoom:50%;">

   3. 단축키

      자주 사용하는 단축키를 메뉴를 통해 확인이 가능하며, 단축키를 통해 특정 기능을 편안하게 사용할 수 있습니다.

      <img src="https://tva1.sinaimg.cn/large/008vOhrAgy1hd508caisvj31wk0m4aei.jpg" style="zoom:50%;">

      

### 개발 과정

1. Use Case Diagram

   <img src="https://tva1.sinaimg.cn/large/008vOhrAgy1hd50mntzmrj316s0twwhw.jpg" style="zoom:50%;">

2. Use Case Scenario

   <img src="https://tva1.sinaimg.cn/large/008vOhrAgy1hd50n4yt9fj316s0twwhw.jpg" style="zoom:50%;">

   <img src="https://tva1.sinaimg.cn/large/008vOhrAgy1hd50n0nmlnj31sc0u0dlp.jpg" style="zoom:50%;">

3. Class Diagram

   <img src="https://tva1.sinaimg.cn/large/008vOhrAgy1hd50mk3c7hj30r40y60ww.jpg" style="zoom:50%;">

4. 상세 Diagram

   <img src="https://tva1.sinaimg.cn/large/008vOhrAgy1hd50n2xqjzj31sg0twdnf.jpg" style="zoom:50%;">