<template>
  <div>
    <!-- 回到顶部按钮 -->
    <div href="#" class="cd-top" v-if="!$common.mobile()" @click="toTop()"></div>

  </div>

</template>

<script>
export default {
  name: "toTop"
}
</script>

<style scoped>

</style>