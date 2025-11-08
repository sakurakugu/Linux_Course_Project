%-------------------------------------------------
% FileName: zscthesis.cls
% Author: Safin (zhaoqid@zsc.edu.cn)
% Version: 0.1
% Date: 2020-05-12
% Description: 导言区
% Others: 如无需要，不用修改本文件
% History: origin 0.1
%------------------------------------------------- 

% latex 版本
\NeedsTeXFormat{LaTeX2e}

% 本文件提供的cls的名字，版本
\ProvidesClass{zscthesis}[2020/05/12 version 0.1]

% ctexart 是 article 和 ctex 的结合，也即支持中文的文章
% ctexbook 是 book 和 ctex 的结合，也即支持中文的书籍
\LoadClass[
oneside,   % 单面排版
a4paper,   % A4纸
titlepage, % 指定标题命令 \maketitle 生成单独的标题页
UTF8,      % UTF-8编码
linespread=1.25, % 行距1.25倍字号大小
zihao=-4,  % 默认字号为小4 
]{ctexbook}



\AtEndOfPackage{% class cfg loaded after package to make preamble commands take effect
    \makeatletter
    \InputIfFileExists{style/zscthesis.cfg}{}{}
    \makeatother
}


% \RequirePackage{cleveref}% 载入自动引用宏包
% \crefname{figure}{图}{图}
% \crefname{table}{表}{表}
% \crefname{equation}{式}{式}
% \renewcommand{\eqref}[1]{\labelcref{#1}~\namecref{#1}}



% debug ---------------------------------------
% 仅编译，不生成PDF，用于debug
% \usepackage{syntonly}
% \syntaxonly

% 页面 ---------------------------------------
% 设置页面边距 (封面单独设置)
% \RequirePackage[top=2.5cm,bottom=2.5cm,left=2.5cm,right=2.5cm]{geometry}
% 上下2.5, 左右2，装订线0.5左，所以left=2.5
\RequirePackage[top=2.5cm,bottom=2.5cm,left=2.5cm,right=2cm]{geometry}
% A4尺寸
% \RequirePackage[left=1.25in,right=1.25in, top=1in,bottom=1in]{geometry}

% 字号字体 ---------------------------------------
% 字号 \zihao{num}
% 0   初号  \zihao{0}
% −0  小初
% 1   一号
% −1  小一
% 2   二号
% −2  小二
% 3   三号
% −3  小三
% 4   四号
% −4  小四
% 5   五号
% -5  小五  \zihao{-5}

% 设置字体  会影响到所有的内容
% texdoc xeCJK
% SimSun KaiTi 通过查找系统字体得到  
% overleaf编译不通过
% AutoFakeBold 当没有声明对应的粗体时，是否使用伪粗体
% \setCJKmainfont[AutoFakeBold=true]{SimSun}  % overleaf 下错误
% \setCJKmainfont[AutoFakeBold=true]{fonts/simsun.ttc}

\RequirePackage{fontspec}

% \setmainfont{Times New Roman}

\setmainfont[NFSSFamily=entextrm]{XITS}[
    Extension      = .otf,
    UprightFont    = *-Regular,
    BoldFont       = *-Bold,
    ItalicFont     = *-Italic,
    BoldItalicFont = *-BoldItalic,
    Ligatures=TeX,
]
\setsansfont[NFSSFamily=entextsf]{XITS}[
    Extension      = .otf,
    UprightFont    = *-Regular,
    BoldFont       = *-Bold,
    ItalicFont     = *-Italic,
    BoldItalicFont = *-BoldItalic,
    Ligatures=TeX,
]
\setmonofont[NFSSFamily=entexttt]{XITS}[
    Extension      = .otf,
    UprightFont    = *-Regular,
    BoldFont       = *-Bold,
    ItalicFont     = *-Italic,
    BoldItalicFont = *-BoldItalic,
    Ligatures=TeX,
]



% 判断当前所处的操作系统
\RequirePackage{ifplatform}

% windows
\ifwindows   
    \setCJKmainfont{SimSun}[AutoFakeBold=2.5,ItalicFont=KaiTi]%
    \setCJKsansfont{SimHei}[AutoFakeBold=2.5]%
    \setCJKmonofont{FangSong}%
\fi

% linux
\iflinux

\fi

% macosx
\ifmacosx
    
    \setCJKmainfont{Songti SC}[%
        UprightFont    = * Light,
        BoldFont       = * Bold,
        ItalicFont     = Kaiti SC,
        BoldItalicFont = Kaiti SC Bold,
    ]
    \setCJKsansfont{Heiti SC}[BoldFont = * Medium]%
    \setCJKmonofont{STFangsong}%
\fi  

 
% /c/windows/Fonts/simsun.ttc
% \setCJKmainfont{simsun.ttc} %宋体
% \setCJKsansfont{msyh.ttf} %微软雅黑
% \setCJKmonofont{FZYTK.ttf} %方正姚体

% 通过查找获得win10系统字体 
% fc-list -f "%{family}\n" :lang=zh > zhfont.txt 
% 参考 xeCJK `texdoc xeCJK`
% Arial Unicode MS
% FangSong,仿宋
% KaiTi,楷体
% Microsoft YaHei,微软雅黑
% MingLiU,細明體
% NSimSun,新宋体
% PMingLiU,新細明體
% SimHei,黑体
% SimSun,宋体




% 新的字体族 
% 宋体已经定义过了， 用法 \songti{xxxx}
% \newCJKfontfamily[song]\songti{SimSun}
% 黑体已经定义过了， 用法 \heiti{xxxx}
% \newCJKfontfamily[hei]\heiti{SimHei}

% 楷体 用法 \kaiti{xxxx}
% \newCJKfontfamily[kai]\kaiti{KaiTi}
% 仿宋体 用法 \fangsongti{xxxx}
% \newCJKfontfamily[fangsong]\fangsongti{FangSong}

% ctex 已经定义的字体
% 除了在 ubuntu 字库中没有
% \fangsong 的定义外，所有字库都有以下四个字体命令。
% \songti 宋体，CJK 等价命令 \CJKfamily{zhsong}。
% \heiti 黑体，CJK 等价命令 \CJKfamily{zhhei}。
% \fangsong 仿宋，CJK 等价命令 \CJKfamily{zhfs}。
% \kaishu 楷书，CJK 等价命令 \CJKfamily







% 章节格式---------------------------------------
% 设置章的标题格式 第X章
% \ctexset {
%     section = {
%         name = {第,章}, 
%         number = \arabic{section},
%     }
% }

\ctexset {
    chapter = {
        % 3号，黑体，居中
        format = \zihao{2}\heiti\centering, 
        % 设置章节的名字
        % name = {第,章}, 
        name = {,}, 
        % 阿拉伯数字序号
        % number = \arabic{chapter},
        number = ,
        % 图目录, 章之间的图标题的距离
        lofskip = {0pt},
        % 表目录, 章之间的表标题的距离
        lotskip = {0pt},
        % 设置章节标题前的垂直间距
        beforeskip = {16pt},
        % 控制章节标题与后面下方之间的距离
        afterskip = {16pt},
        % 上述两个skip才能生效
        fixskip=true,
    },
    section = {
        % 小3号，黑体，居左
        format = \zihao{-3}\heiti\raggedright, 
        name = {,}, 
        number = ,
    },
    subsection = {
        % 4号，黑体，居左
        format = \zihao{4}\heiti\raggedright, 
        name = {,}, 
        number = ,
    },
    subsubsection = {
        % 小4号，黑体，居左
        format = \zihao{-4}\heiti\raggedright,
        name = {,}, 
        number = ,  
    },
}


% 章节编号的深度
% book文档类里默认为2, subsection编号，而subsubsection不编号
% 设置为3, 则subsubsection编号
% depth for the table of contents
\setcounter{secnumdepth}{3} 
% 目录的深度, subsection
\setcounter{tocdepth}{2}

% 这个导引点加了以后，目录，图目录，表目录就不居中
% 目录相关------
% 确保章与页码之间也有引导点
% \usepackage{subfigure}
% \usepackage[subfigure]{tocloft}
% \renewcommand{\cftchapleader}{\cftdotfill{\cftdotsep}}

%---------------------------------------------------------------------------%
%->> Configure table of contents
%---------------------------------------------------------------------------%
%- the table of contents is specified by defining \l@chapter, \l@section, ...
%- most commands are then defined with the \@dottedtocline:
%- \@dottedtocline{⟨level⟩}{⟨indent⟩}{⟨numwidth⟩}{⟨title⟩}{⟨page⟩}
%- ⟨level⟩    an entry is produced only if ⟨level⟩ <= value of the tocdepth counter
%-            note, \chapter is level 0, \section is level 1, etc
%- ⟨indent⟩   indentation from the outer left margin of the start of the contents line
%- ⟨numwidth⟩ width of a box in which the section number is to go
%- <title>    title
%- <page>     page number

%- parameters for spacing and length in toc
% \def\@dotsep{1.5mu}% separation between dots in mu units
%目录导引点过于稀疏， 
\def\@dotsep{0.2mu}
\def\@pnumwidth{2em}% width of a box in which the page number is put
\def\@tocrmarg{2em}% right margin for multiple line entries, \@tocrmarg ≥ \@pnumwidth
\def\@chaptervspace{1ex}% vertical space between chapter titles

%- redefine dottedtocline from classes.dtx and latex.ltx
\renewcommand*{\@dottedtocline}[5]{% [<level>,<indent>,<numwidth>,<title>,<page>]
    \ifnum #1>\c@tocdepth \else
        \vskip \z@ \@plus.2\p@
        {\leftskip #2\relax \rightskip \@tocrmarg \parfillskip -\rightskip
        \parindent #2\relax\@afterindenttrue
        \interlinepenalty\@M
        \leavevmode \zihao{-4}
        \@tempdima #3\relax
        \advance\leftskip \@tempdima \null\nobreak\hskip -\leftskip
        {#4}\nobreak
        \leaders\hbox{$\m@th\mkern \@dotsep \cdot\mkern \@dotsep$}\hfill
        \nobreak
        \hb@xt@\@pnumwidth{\hfil\normalfont \normalcolor #5}%
        \par\penalty\@highpenalty}%
    \fi
}
%- redefine l@part from book.cls to add dotted toc line
\renewcommand*{\l@part}[2]{% [<title>,<page>]
    \ifnum \c@tocdepth >-2\relax
        \addpenalty{-\@highpenalty}%
        \addvspace{2.25em \@plus\p@}%
        \setlength\@tempdima{3em}%
        \begingroup
            \parindent \z@ \rightskip \@pnumwidth
            \parfillskip -\@pnumwidth
            {\leavevmode
            \zihao{-4} #1
            \leaders\hbox{$\m@th\mkern \@dotsep \cdot\mkern \@dotsep$}% add dotted toc line
            \hfil \hb@xt@\@pnumwidth{\hss #2}}\par
            \nobreak
            \global\@nobreaktrue
            \everypar{\global\@nobreakfalse\everypar{}}%
        \endgroup
    \fi
}
%- redefine l@chapter from book.cls to add dotted toc line
\renewcommand*{\l@chapter}[2]{% [<title>,<page>]
    \ifnum \c@tocdepth >\m@ne
        \addpenalty{-\@highpenalty}%
        \vskip \@chaptervspace \@plus\p@
        \setlength\@tempdima{1.5em}%
        \begingroup
            \parindent \z@ \rightskip \@pnumwidth
            \parfillskip -\@pnumwidth
            \leavevmode \zihao{-4}
            \advance\leftskip\@tempdima
            \hskip -\leftskip
            #1\nobreak
            \leaders\hbox{$\m@th\mkern \@dotsep \cdot\mkern \@dotsep$}% add dotted toc line
            \hfil \nobreak\hb@xt@\@pnumwidth{\hss #2}\par
            \penalty\@highpenalty
        \endgroup
    \fi
}
%- redefine indentation for others
\renewcommand*\l@section{\@dottedtocline{1}{1em}{1.8em}}
\renewcommand*\l@subsection{\@dottedtocline{2}{2em}{2.8em}}
\renewcommand*\l@subsubsection{\@dottedtocline{3}{3em}{3.8em}}
\renewcommand*\l@paragraph{\@dottedtocline{4}{4em}{4.8em}}
\renewcommand*\l@subparagraph{\@dottedtocline{5}{5em}{5.8em}}
\renewcommand*\l@figure{\@dottedtocline{1}{1em}{1.8em}}
\renewcommand*\l@table{\@dottedtocline{1}{1em}{1.8em}} 



% 浮动体相关---------------------------------------
% textfraction页面中必须用来排放文本的最小比例。缺省值为 0.2， 即一页中浮动对象所占的比例不得超过 80%。
\renewcommand{\textfraction}{0.15} 
% topfraction页面顶部可以用来放置浮动对象的高度与整个页面高度的最 大比例。缺省值为 0.7，即放置在页顶部的浮动对象所占 的高度不得超过整个页面高度 70%。同样地，如果多个 使用了选项 t 的浮动对象的高度和超过了 整个页面高度的 60%，即使它们的数目没有超过  topnumber 的值，仍将一个也不会被放置 在页面顶部。
\renewcommand{\topfraction}{0.85} 
% bottomfraction页面底部可以用来放置浮动对象的高度与整个页面高度的最 大比例。缺省值为 0.3，这使得如果浮动对象的高度 不超过整个页面高度的 40%，可以允许放置在页面底部。
\renewcommand{\bottomfraction}{0.65} 
% 浮动页中必须由浮动对象占用的最小比例。因此 在一浮动页中空白所占的比例不会超过 1 - \floatpagefraction。缺省值为 0.5。
\renewcommand{\floatpagefraction}{0.60}


% 图，表，公式 ---------------------------------------
% 用于加载图片 includegraphics
\RequirePackage{graphicx}

% 设置图片路径，加载图片可以忽略img前缀
\graphicspath{{img/}}

% 绘图
% \RequirePackage{tikz}
% \usetikzlibrary{3d}
% \usetikzlibrary{graphs}
% \usegdlibrary{trees}



% 抑制图片表格等的浮动 
% \begin{figure}[H] [H]表示把图片放于当前位置
\RequirePackage{float}
% 禁止浮动体跨节
\RequirePackage[section]{placeins}

% 表格宏包
\RequirePackage{booktabs,tabularx,multirow,longtable,makecell}
\RequirePackage{array}


% 重新定义图目录的标题
\renewcommand\listfigurename{图目录}
% 重新定义表目录的标题
\renewcommand\listtablename{表目录}


% 重新定义图的标题前缀
% \renewcommand\figurename{}
% \renewcommand\thefigure{图\arabic{chapter}-\arabic{figure}}

% 重新定义图的标题序号格式 (章号-图号)
% {section}是章的计数器
% {figure}是图的计数器
% 图的标题由 \caption 命令生成
%\renewcommand\thefigure{\arabic{chapter}-\arabic{figure}}
\renewcommand\thefigure{\arabic{figure}}

% \renewcommand\tablename{}
% \renewcommand\thetable{\arabic{chapter}-\arabic{table}}
\renewcommand\thetable{\arabic{table}}

% \caption 命令位于图表下方时，与上方图表的间距
% \setlength{\abovecaptionskip}{10pt}
% \caption 命令位于图表上方时，与下方图表的间距
% \setlength{\belowcaptionskip}{10pt}

% 设置公式编号样式
\makeatletter
\@addtoreset{equation}{chapter}
\makeatother
%\renewcommand\theequation{\arabic{chapter}-\arabic{equation}}
\renewcommand\theequation{\arabic{equation}}

% 设置图，表的 caption的属性
\RequirePackage{caption}

% 设置浮动体标题悬挂缩进
\captionsetup{format=hang}
% 宋体，5号
% 原始的word模板中图表标题的字号只有小五，似乎太小了点
% 把它改成5号
\DeclareCaptionFont{songti}{\songti}
% \DeclareCaptionFont{zihao5}{\zihao{5}} 
% \captionsetup{font={songti, zihao5}, textfont={songti, zihao5}} 
\DeclareCaptionFont{zihaoxiao5}{\zihao{-5}} 
\captionsetup{font={songti, zihaoxiao5}, textfont={songti, zihaoxiao5}}
% labelsep 设置编号和标题之间的符号，默认是冒号colon
\captionsetup{labelsep=space}
% 以下是图片和表格分开来设置
% \captionsetup[figure]{labelsep=space}
% \captionsetup[table]{labelsep=space}


% 以下改变\caption
% \newcommand{\mycaption}[1]{\caption{\zihao{6}\kaishu{#1}}}

% 列表相关 ---------------------------------------
\RequirePackage{enumitem}
% 每一个item第一行缩进
% \parindent 是首行缩进
\setlist[enumerate]{wide=\parindent}
\setlist[itemize]{wide=\parindent} 
% 列表项之间无多余间距，列表和正文之间无多余间距
\setlist{nosep}



% 下划线 颜色 相关 ---------------------------------------
% ulem宏包
% 可断行下划线命令\uline
\RequirePackage{ulem}

% 颜色宏包
\RequirePackage{color,xcolor}

% 参考文献相关 ---------------------------------------
% 载入参考文献宏包，设置引用格式
% natbib宏包配合gbt7714-numerical.bst使用
% number是参考文献显示数字标号
% sort&compress 是排序，以及[2-7]这种形式
% \RequirePackage[numbers, sort&compress]{natbib}

% gbt7714 格式 包含natbib，二者只要一个
% 这个宏包有两种用法，1是宏包，2是bst
% 没有直接使用这个宏包，而是直接使用gbt7714-numerical.bst，是为了定制“出版地不详“，参考 texdoc gbt7714
\RequirePackage[sort&compress]{gbt7714}
% \citestyle{numbers}
% 上角标
\citestyle{super}
% 参考文献页的行距
\setlength{\bibsep}{0.5ex}
% 字体大小  texdoc natbib 
\renewcommand{\bibfont}{\zihao{5}} 
	
% 源代码相关 ---------------------------------------
\RequirePackage{style/zsccode}

% 数学公式相关 ---------------------------------------
\RequirePackage{amsmath}
\RequirePackage{amsfonts} 
\RequirePackage{amsthm}
\RequirePackage{amssymb}
\RequirePackage{newtxmath}
\RequirePackage{esint}

% 页眉页脚相关 ---------------------------------------
% texdoc fancyhdr
\usepackage{fancyhdr}

% 这里的命令是为了代码复用
\newcommand{\myfancy}{
    % 先清空样式
    \fancyhf{}
    % 页脚，居中，页码
    % \fancyfoot[COE]{\thepage} 
    % 页码字号小5
    \fancyfoot[COE]{\zihao{-5}{\thepage}}
    % 页眉，左，内容固定, 宋体，小五
    \fancyhead[LOE]{\songti\zihao{-5}{电子科技大学中山学院实践报告}}
    % 页眉，右，章的题目，宋体，小五
    \fancyhead[ROE]{\songti\zihao{-5}{\leftmark}} 
    % 页眉线宽
    \renewcommand{\headrulewidth}{0.8pt} 
    % 页脚无线
    \renewcommand{\footrulewidth}{0pt}   
}

% 自定义页眉页脚样式
\fancypagestyle{myfancy}{
    \myfancy
}
% 使用自定义样式
\pagestyle{myfancy}

% book文档类的每章第一页为plain格式
% 默认的plain格式，每章第一页不显示页眉
% 重新定义plain样式，在每章第一页使用自定义样式\myfancy
\fancypagestyle{plain}{
    \myfancy
}


% 封面相关 -------------------------------------------

% \newcommand{\ulunify}[1]{\uline{#1}}% unified name
% \newcommand{\ulenhance}[2][1pt]{% enhanced underline
%     \def\ULthickness{#1}% set thickness
%     \setlength{\ULdepth}{0.3em}% set depth
%     \expandafter\ulunify\expandafter{#2}% linebreak fix
% }
% \newcommand{\ulhshift}{-4em}% horizontal shift on underline
% \newcommand{\ulextend}[2][350pt]{% extend underline length
%     \hbox to #1{\hfill\hspace*{\ulhshift}#2\hfill}}

% \RequirePackage{ifxetex}% LaTeX engine detection
% \RequirePackage{etoolbox}% a toolbox of programming facilities
% \newcommand{\zscifstreq}{\expandafter\ifstrequal\expandafter}% expansion control
% \newcommand{\zscifstrbk}{\expandafter\ifblank\expandafter}% expansion control
\RequirePackage{expl3}% LaTeX3 programming environment
\ExplSyntaxOn
\newcommand{\zsclntotab}[2][1pt]{% convert lines into table lines
    \seq_set_split:NnV \l_tmpa_seq {\\} {#2}
    \clist_set_from_seq:NN \l_tmpa_clist \l_tmpa_seq
    \clist_clear:N \l_tmpb_clist
    \clist_map_inline:Nn \l_tmpa_clist
        {%
        \clist_put_right:Nn \l_tmpb_clist 
            { {##1} }
        }
    %\clist_show:N\l_tmpb_clist% show the content of comma list
    \clist_use:Nn \l_tmpb_clist { \\ & }
}
\ExplSyntaxOff

\RequirePackage{changepage}

% 实践名称
\def\defpractice{}
\newcommand{\practice}[1]{\def\defpractice{#1}}
% 专业班级
\def\defmajor{}
\newcommand{\major}[1]{\def\defmajor{#1}}
% 姓名学号
\def\defstudentid{}
\newcommand{\studentid}[1]{\def\defstudentid{#1}}
% 指导教师
\def\defadvisor{}
\newcommand{\advisor}[1]{\def\defadvisor{#1}}
% 实践时间
\def\defpracticedate{}
\newcommand{\practicedate}[1]{\def\defpracticedate{#1}}
% 实践单位
\def\defpracticeinstitute{}
\newcommand{\practiceinstitute}[1]{\def\defpracticeinstitute{#1}}
% 教学单位
\def\defcmdinstitute{}
\newcommand{\cmdinstitute}[1]{\def\defcmdinstitute{#1}}
% 实践地点
\def\defpracticeplace{}
\newcommand{\practiceplace}[1]{\def\defpracticeplace{#1}} 
 


% 位置 左对齐的缩进
% \newcommand{\leftspace}{\hspace{4em}}

% 生成封面，空行用于换行
\newcommand{\mymaketitle}{  
    % 封面单独设置页边距
    \newgeometry{top=2.54cm,bottom=2.54cm,left=3.17cm,right=3.17cm} 
    % 整体居中
    \begin{center}
        % logo 宽度是文本区的宽度
        \includegraphics[width=\textwidth]{logo/uestc}

        % \vspace* 命令产生不会因断页而消失的垂直间距
        % \stretch{⟨n⟩} 生成一个特殊弹性长度，参数 ⟨n⟩ 为权重
        % 弹性长度，是为了防止内容跑到下一页去
        \vspace*{\stretch{1}} 

        % 标题  楷书 小初 伪粗体
        {\kaishu \zihao{-0} \bfseries \deflabeltitle }
        % { \zihao{-0} \bfseries \deflabeltitle }
        % { \zihao{-0}  \deflabeltitle }
        % {\kaishu \zihao{-0} \deflabeltitle }

         

        \vspace*{\stretch{6}}
        
        % flushleft 居左对齐
        % adjustwidth 调整左边距为5em
        \begin{flushleft}\begin{adjustwidth}{5em}{}
            % 行距1.5倍，\linespread{1.5}
            % 楷书 \kaishu 
            % 小二号  
            {\linespread{1.5}\kaishu \zihao{-2}{
                \begin{tabular}{ll} % 表格内容左对齐 

                    % 实践名称
                    \deflabelpractice & \defpractice\\ 

                    % 专业班级
                    \deflabelmajor & \defmajor\\
                     
                    % 姓名学号 团队需要分行
                    \deflabelstudentid & \zsclntotab[0pt]{\defstudentid}\\ 
 
                    % 指导教师 
                    \deflabeladvisor & \defadvisor\\

                    % 实践时间 
                    \deflabelpracticedate & \defpracticedate\\

                    % 实践单位 
                    \deflabelpracticeinstitute & \defpracticeinstitute\\

                    % 教学单位 
                    \deflabelcmdinstitute & \defcmdinstitute\\

                    % 实践地点 
                    \deflabelpracticeplace & \defpracticeplace\\
 
                \end{tabular} 
            }} 
        \end{adjustwidth}\end{flushleft}
        
        \vspace*{\stretch{8}}

        % % 制发单位 仿宋GB2312 三号 
        % {\fangsong \zihao{3} \deflabelzscedu}
        
    \end{center} 
    % 恢复页边距
    \restoregeometry
    
}


% 实践目的
\def\defpracticegoal{}
\newcommand{\practicegoal}[1]{\def\defpracticegoal{#1}}
% 实践安排
\def\defpracticeschedule{}
\newcommand{\practiceschedule}[1]{\def\defpracticeschedule{#1}}
% 实践内容
\def\defpracticework{}
\newcommand{\practicework}[1]{\def\defpracticework{#1}}
% 实践指导书
\def\defpracticeguide{}
\newcommand{\practiceguide}[1]{\def\defpracticeguide{#1}} 

% 实践计划相关 -------------------------------------------
% 生成实践计划

\newcommand{\makepracplan}{
    % 行距宽松
    \renewcommand\arraystretch{1.2}

    \begin{table}[htbp]
        \centering   
        % 垂直居中固定宽度, 超过宽度自动换行 m{2em} 水平居中{\centering}  
        \begin{tabular}{|m{2em}<{\centering}|m{30em}|} 

            \hline 
            \zihao{-3}{\deflabelpracticegoal} &\defpracticegoal  \\ 

            \hline 
            \zihao{-3}{\deflabelpracticeschedule} &  \defpracticeschedule  \\ 

            \hline  
            \zihao{-3}{\deflabelpracticework}  &   \defpracticework  \\ 
            
            \hline  
            \zihao{-3}{\deflabelpracticeguide} &    \defpracticeguide  \\ 
            
            \hline 
            
        \end{tabular}  
    \end{table}
}


% \newcommand{\makepracplan}{

    

%     % 行距宽松
%     % \renewcommand\arraystretch{1.8}

%     \begin{table}[htbp]
%         \centering        
%         \begin{tabular}{|p{2em}|p{10em}|}

%             \hline 
%             \deflabelpracticegoal & \begin{tabular}[c]{@{}l@{}} { \defpracticegoal } \end{tabular}  \\ 

%             \hline 
%             \deflabelpracticeschedule &  \begin{tabular}[c]{@{}l@{}} { \defpracticeschedule } \end{tabular} \\ 

%             \hline  
%             \deflabelpracticework  & 
%             \begin{tabular}[c]{@{}l@{}} { \defpracticework } \end{tabular}  \\ 
            
%             \hline  
%             \deflabelpracticeguide &  
%             \begin{tabular}[c]{@{}l@{}} { \defpracticeguide } \end{tabular} \\ 
            
%             \hline 
            
%         \end{tabular}  
%     \end{table}
% }


% \multicolumn{1}{|c|}{ \defpracticegoal }

% 成绩评定相关 -------------------------------------------
% 生成成绩评定
\newcommand{\makeevaluation}{

 

    % 行距宽松
    \renewcommand\arraystretch{1.8}

    \begin{table}[htbp]
        \centering        
        \begin{tabular}{|l|c|}
            \hline 
            评分项目 & 得分  \\ 
            \hline 
            考勤情况（10\%） &    \\ 
            \hline 
            工作态度（10\%） &   \\ 
            \hline 
            实训报告（10\%） &    \\ 
            \hline 
            应用数学知识、计算机原理与技术、软件工程理论与方法的能力（10\%） &    \\ 
            \hline 
            开发实践所需技术、方法及使用现代工具的能力（10\%） &    \\ 
            \hline 
            设计、开发、维护及管理计算机程序与软件系统的能力（10\%） &    \\
            \hline 
            项目管理、有效沟通、领域整合与团队协作的能力（10\%） &    \\
            \hline 
            研究及应用科技成果、解决综合性复杂性信息问题的能力（10\%） &    \\
            \hline 
            了解技术前沿与产业趋势及其影响，培养持续学习的习惯与能力（10\%） &    \\
            \hline 
            理解及遵守专业伦理、职业道德及职业规范，认知社会责任（10\%） &    \\
            \hline 
            总分 &    \\
            \hline 
        \end{tabular}  
    \end{table}

    \vspace*{\stretch{16}}

    { {\deflabelteacher \rule[-.4pt]{8em}{.4pt} \hspace*{1em} \deflabelteachername \hspace*{2em} \deflabeldate  }}
   

}
 
    

% 例子相关 ---------------------------------------------
\RequirePackage{style/zscexample}



% 超链接相关 -------------------------------------------
% 为减少可能的冲突，习惯上将 hyperref 宏包放在其它宏包之后调用
% 对于章节命令 \chapter、 \section等，默认情况下会为 PDF 自动生成书签
% bookmarks=⟨true|false⟩ 默认生成书签
% hidelinks=true 取消链接的颜色和边框
% bookmarksnumbered=true 书签带章节号
\usepackage[hidelinks,bookmarksnumbered=true]{hyperref}