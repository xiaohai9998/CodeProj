<template>
  <div>
    <!-- el过渡动画 -->
    <transition name="el-fade-in-linear">
      <div class="toolbar-content" >
        <!-- 导航列表 -->
        <div class="scroll-menu-block">
          <ul class="scroll-menu">
            <li>
              <div class="my-menu">
                🏡 <span>首页</span>
              </div>
            </li>
            <li>
              <div class="my-menu">
                📒 <span>开发笔记</span>
              </div>
            </li>

            <!-- 爱情买卖 -->
            <li>
              <div class="my-menu">
                💋 <span>收获爱情</span>
              </div>
            </li>

            <!-- 留言 -->
            <li>
              <div class="my-menu">
                📪 <span>留言</span>
              </div>
            </li>
            <!-- 友人帐 -->
            <li>
              <div class="my-menu">
                💃 <span>友人帐</span>
              </div>
            </li>

            <!-- 关于 -->
            <li>
              <div class="my-menu">
                🐟 <span>关于</span>
              </div>
            </li>
          </ul>
        </div>
      </div>
    </transition>
  </div>
</template>

<script>
export default {
  name: "myHead"
}
</script>

<style scoped>
  .toolbar-content {
    width: 100%;
    height: 60px;
    /* 固定位置，不随滚动条滚动 */
    position: fixed;
    z-index: 100;
    /* 禁止选中文字 */
    user-select: none;
    transition: all 0.3s ease-in-out;
    display: inline-block;
  }

  .toolbar-content.enter {
    background: rgba(255, 255, 255, 1);
    color: #333333;
    box-shadow: 0 1px 3px 0 rgba(0, 34, 77, 0.05);
  }

  .toolbar-content.hoverEnter {
    background: rgba(0, 0, 0, 0.5);
    box-shadow: 0 1px 3px 0 rgba(0, 34, 77, 0.05);
  }

  .scroll-menu {
    margin: 0 80px 0 0;
    display: flex;
    justify-content: flex-end;
    padding: 0px;
  }

  .scroll-menu > li {
    list-style: none;
    margin: 0 12px;
    font-size: 17px;
    height: 60px;
    line-height: 60px;
    position: relative;
    cursor: pointer;
  }

  .scroll-menu > li:hover .my-menu span {
    color: orange;
  }

  .scroll-menu > li:hover .my-menu i {
    color: orange;
    animation: scale 1.5s ease-in-out infinite;
  }

  .scroll-menu > li .my-menu:after {
    content: "";
    display: block;
    position: absolute;
    bottom: 0;
    height: 6px;
    background-color: orange;
    width: 100%;
    max-width: 0;
    transition: max-width 0.25s ease-in-out;
  }

  .scroll-menu > li:hover .my-menu:after {
    max-width: 100%;
  }

</style>