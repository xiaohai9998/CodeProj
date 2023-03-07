<template>
  <div class="myFooter">
    <div class="footer-title">云想衣裳花想容,&nbsp;春风拂槛露华浓
    </div>
    <div class="icp">© 2023&nbsp;开发笔记
      <a href="https://beian.miit.gov.cn/#/Integrated/index" target="_blank">&nbsp;冀ICP备2021018143号-1&nbsp;</a>
      <a href="http://www.beian.gov.cn/portal/registerSystemInfo?recordcode=13043302000149" target="_blank">
        冀公网安备 13043302000149号
      </a>
    </div>
  </div>
</template>

<script>
  export default {
    props: {

    },
    data() {
      return {}
    },
    created() {
    }
  }
</script>

<style scoped>
  .myFooter-wrap {
    user-select: none;
    animation: hideToShow 2s;
  }
  @font-face {
    font-family: "myFont";
    src: url('../assets/fonts/ZhuZiAWan.ttc');
  }

  .myFooter {
    font-family: "myFont";
    border-radius: 0.6rem 0.6rem 0 0;
    text-align: center;
    color: white;
    /* 背景渐变色 - 第一步是设置容器大小，我容器里有东西，故就不用设置了，这是第二步 ，注意顺序不能错，错了就乱了*/
    background: linear-gradient(-45deg, #ee7752, #e73c7e, #23a6d5, #23d5ab);
    /* 背景尺寸 - 第三步 */
    background-size: 300% 300%;
    /* 循环动画 - 第四步 */
    animation: gradientBG 10s ease infinite;
  }
  /* 背景位置移动 */
  @keyframes gradientBG {
    0% {
      background-position: 0 50%;
    }

    50% {
      background-position: 100% 50%;
    }

    100% {
      background-position: 0 50%;
    }
  }

  .footer-title {
    padding-top: 10px;
    font-size: 20px;
  }

  .icp, .icp a {
    color: #595A5A;
    font-size: 15px;
  }

  .icp {
    padding-top: 10px;
    padding-bottom: 10px;
  }

  .icp a {
    text-decoration: none;
    transition: all 0.3s;
  }

  .icp a:hover {
    color: orange;
  }

</style>
