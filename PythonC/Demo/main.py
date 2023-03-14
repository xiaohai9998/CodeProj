
def print_hi(name):
    print(f'Hi, {name}')  

#Hello呀
if __name__ == '__main__':
    print_hi('Hello')

from datetime import datetime
import odps
import xlwt
import os
from odps import DataFrame
import pandas as pd
import xlrd
import numpy as np
from collections import defaultdict
from collections import Counter

# 写入工作簿
def write_imf(fl_save_path, data):
    wb = xlwt.Workbook(encoding='utf-8')  # 不写encoding会出现编码错误
    sh = wb.add_sheet(u'data', cell_overwrite_ok=True)

    # 表头部分,单独写
    colnames = data.columns.values
    for i in range(0, data.shape[1]):
        sh.write(0, i, colnames[i])
    # 表内容,循环写入,好像没简便的方法

    for i in range(1, len(data) + 1):
        for j in range(0, data.shape[1]):
            value = data.iloc[i - 1, j]
            # print(value)
            # 这里的坑特别多！！！数据读进来之后就成numpy.xxx64的类型了，在dataframe的时候就需要统一干掉！
            try:
                value.dtype
                if value.dtype == 'int64':
                    value = int(value)
                # print('value is:%d,type is:%s'%(value,type(value)))
                if value.dtype == 'float64':
                    value = float(value)
                    # print('value is:%d,type is:%s' % (value, type(value)))
            except(RuntimeError, TypeError, NameError, ValueError, AttributeError):
                pass
            sh.write(i, j, value)

    wb.save(fl_save_path)
    print('congratulation save successful!')

def save_pd_to_csv(fl_save_path, data):
    try:
        # 直接转csv不加encoding，中文会乱码
        data.to_csv(fl_save_path, encoding="utf_8_sig", header=True, index=False)  # 存储
        return True
    except:
        return False

def get_excel_content(file_path):
    # 获取excel内的SQL语句，需要通过xlrd获取workbook中的SQL内容，或者读txt，后续改为配置文件
    wb = xlrd.open_workbook(file_path, encoding_override='utf-8')
    sht = wb.sheet_by_index(0)  # 默认第一个工作表
    # print(sht.name)
    wb_cont_imf = []
    nrows = sht.nrows  # 行数
    wb_cont_imf = [sht.row_values(i) for i in range(0, nrows)]  # 第一个工作表内容按行循环写入
    df = pd.DataFrame(wb_cont_imf[1:], columns=wb_cont_imf[0])
    return df

# 获取年月第一天最后一天
def getMonthFirstDayAndLastDay(year=None, month=None):
    """
    :param year: 年份，默认是本年，可传int或str类型
    :param month: 月份，默认是本月，可传int或str类型
    :return: firstDay: 当月的第一天，datetime.date类型
              lastDay: 当月的最后一天，datetime.date类型
    """
    if year:
        year = int(year)
    else:
        year = datetime.date.today().year
    if month:
        month = int(month)
    else:
        month = datetime.date.today().month

    # 获取当月第一天的星期和当月的总天数
    firstDayWeekDay, monthRange = calendar.monthrange(year, month)

    # 获取当月的第一天
    firstDay = datetime.date(year=year, month=month, day=1)
    lastDay = datetime.date(year=year, month=month, day=monthRange)​
    # return firstDay, lastDay
    return lastDay

# dataframe2png
def render_mpl_table(data, col_width=5.0, row_height=0.625, font_size=1,
                     header_color='#40466e', row_colors=['#f1f1f2', 'w'], edge_color='w',
                     bbox=[0, 0, 1, 1], header_columns=0,
                     ax=None,**kwargs):
    if ax is None:
        # size = (np.array(data.shape[::-1]) + np.array([0, 1])) * np.array([col_width, row_height])
        # fig, ax = plt.subplots(figsize=size)
        fig, ax = plt.subplots() # 创建一个空的绘图区
        # 衍生知识点，服务器上安装中文字体
        plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
        # plt.rcParams['font.sans-serif'] = ['WenQuanYi Zen Hei Mono']
        plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号
        plt.style.use('ggplot')
        ax.axis('off')

    mpl_table = ax.table(cellText=data.values, bbox=bbox, colLabels=data.columns, **kwargs)

    mpl_table.auto_set_font_size(False)
    mpl_table.set_fontsize(font_size)

    for k, cell in six.iteritems(mpl_table._cells):
        cell.set_edgecolor(edge_color)
        nrow = k[0]
        ncol = k[1]
        # 设置表格底色
        if nrow == 0 or ncol < header_columns:
            cell.set_text_props(weight='bold', color='w')
            cell.set_facecolor(header_color)
        else:
            cell.set_facecolor(row_colors[k[0] % len(row_colors)])

    # # 对当日异常数据为0的部分，着重体现
    # row_num = []
    # for k, cell in mpl_table._cells.items():
    #     nrow = k[0]
    #     ncol = k[1]
    #     val = cell.get_text().get_text()
    #     if nrow > 0 and ncol == 2 and val != '0':
    #         row_num.append(nrow)
    # for k, cell in six.iteritems(mpl_table._cells):
    #     nrow = k[0]
    #     # 设置表格底色
    #     if nrow in row_num:
    #         cell.set_facecolor('gold')

    # 保留原图的设置
    # fig.set_size_inches(width/100.0,height/100.0)#输出width*height像素
    plt.gca().xaxis.set_major_locator(plt.NullLocator())
    plt.gca().yaxis.set_major_locator(plt.NullLocator())
    plt.subplots_adjust(top=1, bottom=0, left=0, right=1, hspace=0, wspace=0)
    plt.margins(0, 0)

    return ax
