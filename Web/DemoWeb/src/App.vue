<template>
  <div>
    <myHead></myHead>
    <demoH></demoH>
    <!-- 页脚 -->
    <myFooter></myFooter>
  </div>
</template>

<script>
import myHead from "@/components/myHead.vue";
import demoH from "@/components/demoH.vue";
import myFooter from "@/components/myFooter.vue";

export default {
  name: 'App',
  components: {
    myHead,
    demoH,
    myFooter
  }
}
</script>

<style>

</style>
