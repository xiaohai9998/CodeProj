<template>
  <div class="myFooter">
    <div class="footer-title">云想衣裳花想容,&nbsp;春风拂槛露华浓
    </div>
    <div class="icp">© 2023&nbsp;&nbsp;开发笔记
      <a href="https://beian.miit.gov.cn/#/Integrated/index" target="_blank">&nbsp;&nbsp;冀ICP备2021018143号-1</a>
      <a href="http://www.beian.gov.cn/portal/registerSystemInfo?recordcode=13043302000149" target="_blank">
        &nbsp;&nbsp;冀公网安备 13043302000149号
      </a>&nbsp;&nbsp;联系方式：xiaohai9998@126.com
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

  .myFooter {
    border-radius: 0.6rem 0.6rem 0 0;
    text-align: center;
    color: white;
    background: linear-gradient(-45deg, #23a6d5, #23d5ab);
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
