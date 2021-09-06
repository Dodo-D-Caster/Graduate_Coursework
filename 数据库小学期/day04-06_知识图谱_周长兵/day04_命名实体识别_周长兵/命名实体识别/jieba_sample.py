# 导入 jieba
import jieba
import jieba.posseg as pseg  # 词性标注
import jieba.analyse as anls  # 关键词提取

# 全模式
seg_list = jieba.cut("他来到上海交通大学吃蜜雪冰城", cut_all=True)
print("【全模式】：" + "/ ".join(seg_list))


# 精确模式
seg_list = jieba.cut("他来到上海交通大学", cut_all=False)
print("【精确模式】：" + "/ ".join(seg_list))

# 搜索引擎模式
seg_list = jieba.cut_for_search("他毕业于上海交通大学机电系，后来在一机部上海电器科学研究所工作")
print("【搜索引擎模式】：" + "/ ".join(seg_list))

# 关键词提取
s = "此外，公司拟对全资子公司吉林欧亚置业有限公司增资4.3亿元，增资后，" \
    "吉林欧亚置业注册资本由7000万元增加到5亿元。吉林欧亚置业主要经营范围为房地产开发及百货零售等业务。" \
    "目前在建吉林欧亚城市商业综合体项目。2013年，实现营业收入0万元，实现净利润-139.13万元。"
for x, w in anls.extract_tags(s, topK=5, withWeight=True):
    print('%s %s' % (x, w))


