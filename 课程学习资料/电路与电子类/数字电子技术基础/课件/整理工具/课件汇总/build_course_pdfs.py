from pathlib import Path
import json, re, sys, tempfile, atexit
from xml.sax.saxutils import escape
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.lib import colors
from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import ParagraphStyle
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer, PageBreak, Table, TableStyle, KeepTogether
from pypdf import PdfReader, PdfWriter
from pypdf.annotations import Link
from course_map import CHAPTERS, LECTURES

TOOL_DIR = Path(__file__).resolve().parent
ROOT = TOOL_DIR.parents[1]
temp_workspace = tempfile.TemporaryDirectory(prefix='digital-electronics-pdf-')
atexit.register(temp_workspace.cleanup)
TMP = Path(temp_workspace.name)
SUMMARY_DIR = ROOT / '复习资料'
MERGED_DIR = ROOT / '课件'
SUMMARY_DIR.mkdir(parents=True, exist_ok=True)
pdfmetrics.registerFont(TTFont('CN', 'C:/Windows/Fonts/msyh.ttc', subfontIndex=0))
pdfmetrics.registerFont(TTFont('CNB', 'C:/Windows/Fonts/msyhbd.ttc', subfontIndex=0))
W,H = A4
M=43
CW=W-2*M
NAVY=colors.HexColor('#15334A')
TEAL=colors.HexColor('#166F78')
INK=colors.HexColor('#283645')
GREY=colors.HexColor('#647587')
LIGHT=colors.HexColor('#EEF5F7')
styles={
 'title':ParagraphStyle('title',fontName='CNB',fontSize=23,leading=34,textColor=NAVY,spaceAfter=16,wordWrap='CJK'),
 'page':ParagraphStyle('page',fontName='CNB',fontSize=19,leading=28,textColor=NAVY,spaceAfter=10,wordWrap='CJK'),
 'h':ParagraphStyle('h',fontName='CNB',fontSize=11.8,leading=18,textColor=TEAL,spaceBefore=9,spaceAfter=4,wordWrap='CJK',keepWithNext=True),
 'body':ParagraphStyle('body',fontName='CN',fontSize=10,leading=16.3,textColor=INK,spaceAfter=6,wordWrap='CJK'),
 'small':ParagraphStyle('small',fontName='CN',fontSize=8.4,leading=13,textColor=GREY,spaceAfter=7,wordWrap='CJK'),
 'formula':ParagraphStyle('formula',fontName='CN',fontSize=10,leading=16,textColor=NAVY,backColor=LIGHT,borderPadding=6,spaceBefore=4,spaceAfter=9,wordWrap='CJK'),
 'cell':ParagraphStyle('cell',fontName='CN',fontSize=8.8,leading=13.2,textColor=INK,wordWrap='CJK'),
 'headcell':ParagraphStyle('headcell',fontName='CNB',fontSize=8.8,leading=13.2,textColor=colors.white,wordWrap='CJK'),
 'indexcell':ParagraphStyle('indexcell',fontName='CN',fontSize=8.1,leading=11.5,textColor=INK,wordWrap='CJK'),
}

SUP_MAP=dict(zip('⁰¹²³⁴⁵⁶⁷⁸⁹⁻⁺⁼⁽⁾ᴺᶠⁿᵏⁱᵗ','0123456789-+=()NF nkit'.replace(' ','')))
SUP_MAP['ᴬ']='A'
SUB_MAP=dict(zip('₀₁₂₃₄₅₆₇₈₉₊₋₌₍₎ᵢ','0123456789+-=()i'))

def markup(text):
    value=escape(str(text)).replace('\n','<br/>')
    value=re.sub('['+''.join(SUP_MAP)+']+',lambda m:'<super>'+''.join(SUP_MAP[c] for c in m.group())+'</super>',value)
    value=re.sub('['+''.join(SUB_MAP)+']+',lambda m:'<sub>'+''.join(SUB_MAP[c] for c in m.group())+'</sub>',value)
    return value

def p(text, kind='body'):
    return Paragraph(markup(text), styles[kind])

def table(rows, widths=None, compact=False):
    n=len(rows[0])
    if widths is None:
        widths={2:[CW*.26,CW*.74],3:[CW*.20,CW*.43,CW*.37],4:[CW*.28,CW*.13,CW*.13,CW*.46]}[n]
    content=[[p(str(x),'headcell' if i==0 else ('indexcell' if compact else 'cell')) for x in row] for i,row in enumerate(rows)]
    t=Table(content,colWidths=widths,hAlign='LEFT',repeatRows=1)
    t.setStyle(TableStyle([
        ('BACKGROUND',(0,0),(-1,0),NAVY),('VALIGN',(0,0),(-1,-1),'TOP'),
        ('ROWBACKGROUNDS',(0,1),(-1,-1),[colors.white,LIGHT]),
        ('LEFTPADDING',(0,0),(-1,-1),6),('RIGHTPADDING',(0,0),(-1,-1),6),
        ('TOPPADDING',(0,0),(-1,-1),3.5 if compact else 5),('BOTTOMPADDING',(0,0),(-1,-1),3.5 if compact else 5),
        ('LINEBELOW',(0,0),(-1,0),.5,TEAL),('LINEBELOW',(0,-1),(-1,-1),.5,colors.HexColor('#CFDEE4'))]))
    return t

class Title(Paragraph):
    def __init__(self,text,key,category=None):
        super().__init__(markup(text),styles['title'] if key=='cover' else styles['page'])
        self.key=key
        self.category=category
        self.heading=text

class CourseDoc(SimpleDocTemplate):
    def __init__(self,*args,**kwargs):
        super().__init__(*args,**kwargs)
        self.locations={}
        self.last_category=None
    def afterFlowable(self,f):
        if isinstance(f,Title):
            self.locations[f.key]=self.page-1
            self.canv.bookmarkPage(f.key)
            if f.category and f.category not in ('extra','check'):
                if f.category != self.last_category:
                    ch=next(c for c in CHAPTERS if c['id']==f.category)
                    self.canv.addOutlineEntry(ch['title'],f.key,0,False)
                    self.last_category=f.category
                self.canv.addOutlineEntry(f.heading,f.key,1,False)
            else:
                self.canv.addOutlineEntry(f.heading,f.key,0,False)
                self.last_category=None

def footer(canvas,doc):
    canvas.saveState()
    canvas.setStrokeColor(colors.HexColor('#CADAE1'))
    canvas.line(M,39,W-M,39)
    canvas.setFont('CN',8)
    canvas.setFillColor(GREY)
    canvas.drawString(M,25,'数字电子技术基础 · 阎石第六版章节对照')
    canvas.drawRightString(W-M,25,str(doc.page))
    canvas.restoreState()

sources=[]
offsets={}
total=0
for i in range(1,26):
    f=ROOT/'课件'/f'L{i:02d}.2025.pdf'
    r=PdfReader(f)
    offsets[i]=total
    total+=len(r.pages)
    sources.append((i,f,r))

def merged_page(lecture,page):
    return 3+offsets[lecture]+page  # human one-based, 3 front pages

chapter_rows=[['课本章节 / 正文起始页','主要课件位置','合订本起始页']]
for ch in CHAPTERS:
    l,pg=ch['start']
    chapter_rows.append([f"{ch['title']} · 课本 p{ch['book']}",ch['source'],str(merged_page(l,pg))])

lecture_rows=[['讲次 / 原页数','内容','课本对应','合订本页']]
for (i,f,r),(title,chapters) in zip(sources,LECTURES):
    lecture_rows.append([f'L{i:02d} / {len(r.pages)} 页',title,chapters,f'{merged_page(i,1)}-{merged_page(i,len(r.pages))}'])

def front_story(summary=False):
    story=[Title('数字电子技术基础\n'+('课件复习总结' if summary else '课件合订本'),'cover'),Spacer(1,18)]
    story.extend([p('依据阎石《数字电子技术基础》第六版整理','h'),p(f'25 份课件 · {total} 页原件 · 第1-8章与补充内容','body'),Spacer(1,18)])
    story.append(p('整理依据','h'))
    story.append(p('材料为“课件”目录下 L01.2025.pdf 至 L25.2025.pdf。课本版本、章名、小节与正文页码已按“教材”目录中的《数字电子技术基础.pdf》目录核对。'))
    story.append(p('如何使用','h'))
    if summary:
        story.append(p('先看章节总结与解题方法，再用来源标注查回原课件的电路图、波形和例题。左侧书签可以按章及专题跳转；下两页提供课本对照和原讲次索引。'))
    else:
        story.append(p('左侧书签按“课本章 → 小节/专题”组织，并提供按 L01-L25 的原讲次入口。下两页提供课本对照和讲次页码。课件按原讲次连续合并，保持原图、原字、原顺序。'))
    story.append(p('页码约定','h'))
    story.append(p('“Lxx pN”指原课件 PDF 第 N 页，每页通常有四张幻灯片；“课本 pN”指书上印刷正文页码；“合订本页”指新 PDF 从封面起计算的实体页码。章间交界可落在同一页，因此不同章节书签可能共享一个原页。'))
    story.append(p('编号与资料年份','h'))
    story.append(p('课件的部分小节编号沿用旧编排，本资料按第六版校正：如课件 TTL 的 3.5 对应课本 3.4，MUX 的 4.3.3 对应 4.4.3，边沿/脉冲触发的 5.3.2/5.3.3 也需按主题对应。流水线、信息编码等以“补充”标明。'))
    story.append(p('课件标注 2025 秋；教学安排.pdf 标注 2026 春，讲次不同。本资料按实际课件内容整理；历史考试安排与“不要求”说明不用于判断当前学期要求。原文件均未改动。','small'))
    story.extend([p('整理日期：2026-10-08','small'),PageBreak(),Title('课本章节与课件对照','chapter-map')])
    story.append(table(chapter_rows,[CW*.37,CW*.49,CW*.14]))
    story.append(Spacer(1,10))
    story.append(p('PLD 专题：L15 p9-12、L23 p2-7，对应课本 4.6-4.8、6.5 与附录一。该专题在第4章和第6章书签内均提供入口。','small'))
    story.append(p('交界页：L03 p6（第1/2章）、L05 p6（第2/3章）、L13 p4（第3/4章）、L18 p7（第5/6章）、L23 p7（PLD/第7章）。第8章正文从 L25 p5 开始。','small'))
    story.extend([PageBreak(),Title('L01-L25 原讲次索引','lecture-index')])
    story.append(table(lecture_rows,[CW*.14,CW*.47,CW*.23,CW*.16],compact=True))
    story.append(Spacer(1,8))
    story.append(p('表中“合订本页”指《数字电子技术基础_课件合订本_课本章节书签.pdf》。合订本前 3 页为新增导航，后 186 页为完整原课件。','small'))
    return story

cover_path=TMP/'merge_front.pdf'
frontdoc=CourseDoc(str(cover_path),pagesize=A4,rightMargin=M,leftMargin=M,topMargin=43,bottomMargin=52,
    title='数字电子技术基础 · 课件合订本导航',author='课程资料整理')
frontdoc.build(front_story(),onFirstPage=footer,onLaterPages=footer)
assert len(PdfReader(cover_path).pages)==3, 'Front pages changed; update all page references.'

blocks=(TOOL_DIR/'summary_content.txt').read_text(encoding='utf-8').split('\n===\n')
story=front_story(summary=True)
for i,block in enumerate(blocks):
    lines=block.strip().splitlines()
    category,title=lines[0][1:].split('|',1)
    story.extend([PageBreak(),Title(title,f'content-{i}',category),p(lines[1],'small')])
    j=2
    while j<len(lines):
        kind,text=lines[j].split('|',1)
        if kind=='T':
            rows=[text.split('|')]
            j+=1
            while j<len(lines) and lines[j].startswith('R|'):
                rows.append(lines[j][2:].split('|'))
                j+=1
            story.extend([table(rows),Spacer(1,7)])
            continue
        story.append(p(('• '+text) if kind=='B' else text,{'H':'h','P':'body','B':'body','F':'formula'}[kind]))
        j+=1

summary_path=SUMMARY_DIR/'数字电子技术基础_课件复习总结_按课本章节.pdf'
summarydoc=CourseDoc(str(summary_path),pagesize=A4,rightMargin=M,leftMargin=M,topMargin=43,bottomMargin=52,
    title='数字电子技术基础 · 课件复习总结 · 阎石第六版',author='课程资料整理')
summarydoc.build(story,onFirstPage=footer,onLaterPages=footer)
summary_reader=PdfReader(summary_path)
assert len(summary_reader.pages)==3+len(blocks), f'Summary overflow: expected {3+len(blocks)}, got {len(summary_reader.pages)}'

if '--summary-only' in sys.argv:
    print('Summary regenerated:',len(summary_reader.pages),'pages')
    sys.exit(0)

writer=PdfWriter()
writer.append(cover_path,import_outline=False)
for i,f,r in sources:
    writer.append(r,import_outline=False)
writer.add_metadata({'/Title':'数字电子技术基础 · L01-L25课件合订本 · 阎石第六版章节书签','/Author':'课程资料整理','/Subject':'完整原课件、课本章节与专题书签、讲次索引'})
writer.page_mode='/UseOutlines'
nav=writer.add_outline_item('阅读导航与章节对照',0)
writer.add_outline_item('课本章节与课件对照',1,parent=nav)
writer.add_outline_item('L01-L25 原讲次索引',2,parent=nav)
outline_manifest=[]
for ch in CHAPTERS:
    l,pg=ch['start']
    dest=merged_page(l,pg)-1
    parent=writer.add_outline_item(f"{ch['title']}（课本 p{ch['book']}）",dest)
    outline_manifest.append({'title':ch['title'],'merged_page':dest+1,'lecture':l,'source_page':pg})
    for title,l,pg in ch['sections']:
        assert 1<=pg<=len(sources[l-1][2].pages)
        dest=merged_page(l,pg)-1
        writer.add_outline_item(f'{title} | L{l:02d} p{pg}',dest,parent=parent)
        outline_manifest.append({'title':title,'merged_page':dest+1,'lecture':l,'source_page':pg})
extra=writer.add_outline_item('补充专题：PLD / FPGA / EDA',merged_page(15,9)-1)
for title,l,pg in [('PLD、HDL 与 EDA 导学',15,9),('FPLA、PAL、GAL、EPLD',23,2),('CPLD 与 SRAM 型 FPGA',23,5),('配置装载与设计流程',23,6)]:
    writer.add_outline_item(f'{title} | L{l:02d} p{pg}',merged_page(l,pg)-1,parent=extra)
index=writer.add_outline_item('按原讲次查找：L01-L25',merged_page(1,1)-1)
for (i,f,r),(title,chapters) in zip(sources,LECTURES):
    writer.add_outline_item(f'L{i:02d} · {title} [{chapters}]',merged_page(i,1)-1,parent=index)
merged_path=MERGED_DIR/'数字电子技术基础_课件合订本_课本章节书签.pdf'
writer.write(merged_path)

merged_reader=PdfReader(merged_path)
assert len(merged_reader.pages)==total+3
for i,f,r in sources:
    for j,page in enumerate(r.pages):
        target=merged_reader.pages[3+offsets[i]+j]
        assert page.mediabox==target.mediabox
        a=page.get_contents()
        b=target.get_contents()
        assert (a.get_data() if a else b'')==(b.get_data() if b else b''), f'Page content changed: L{i} p{j+1}'
        assert (page.extract_text() or '')==(target.extract_text() or '')

def outline_count(items,reader):
    n=0
    for item in items:
        if isinstance(item,list): n+=outline_count(item,reader)
        else:
            dest=reader.get_destination_page_number(item)
            assert 0<=dest<len(reader.pages), str(item)
            n+=1
    return n

report={'source_files':25,'source_pages':total,'merged_pages':len(merged_reader.pages),
        'summary_pages':len(summary_reader.pages),'merged_bookmarks':outline_count(merged_reader.outline,merged_reader),
        'summary_bookmarks':outline_count(summary_reader.outline,summary_reader),
        'original_page_content_verified':True,'chapter_bookmarks':outline_manifest,
        'summary_heading_locations':summarydoc.locations,
        'outputs':[str(merged_path),str(summary_path)]}
(TOOL_DIR/'validation.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps({k:v for k,v in report.items() if k not in ('chapter_bookmarks','summary_heading_locations')},ensure_ascii=False,indent=2))
