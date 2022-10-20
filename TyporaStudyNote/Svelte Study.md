# Svelte Study

## 1. 组件格式

All three sections — **script**, **styles** and **markup**

```
<script>
	// logic goes here
</script>

<!-- markup (zero or more items) goes here -->

<style>
	/* styles go here */
</style>
```

### <脚本>

##### 有四个附加规则

1. **`export`创建组件道具**

   Svelte 使用`export`关键字将变量声明标记为属性，这意味着组件的使用者可以访问它

   ```
   <script>
   	export let foo;
   
   	// Values that are passed in as props
   	// are immediately available
   	console.log({ foo });
   </script>
   ```

   在开发模式下（参见[编译器选项](https://svelte.dev/docs#compile-time-svelte-compile)），如果没有提供默认初始值并且消费者没有指定值，则会打印警告。要消除此警告，请确保指定默认初始值，即使它是`undefined`.

   ```
   <script>
   	export let bar = 'optional default initial value';
   	export let baz = undefined;
   </script>
   ```

   可以使用保留字作为道具名称。

   ```
   <script>
   	let className;
   	// creates a `class` property, even
   	// though it is a reserved word
   	export { className as class };
   </script>
   ```

   

2. **作业是“被动的”**

   更改组件状态并触发重新渲染，只需分配给本地声明的变量

   ```
   <script>
   	let count = 0;
   
   	function handleClick () {
   		// calling this function will trigger an
   		// update if the markup references `count`
   		count = count + 1;
   	}
   </script>
   ```

   ```
   <script>
   	let arr = [0, 1];
   
   	function handleClick () {
   		// this method call does not trigger an update
   		//例如.push()并且.splice()不会自动触发更新。需要后续分配才能触发更新
   		arr.push(2);
   		// this assignment will trigger an update
   		// if the markup references `arr`
   		arr = arr
   	}
   </script>
   ```

   

3. .`$:`将声明标记为反应式

   任何顶级语句（即不在块或函数内）都可以通过在其前面加上`$:` [JS 标签语法](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/label)来进行反应。响应式语句在组件更新之前立即运行，只要它们所依赖的值发生了变化。

   ```
   <script>
   	export let title;
   
   	// this will update `document.title` whenever
   	// the `title` prop changes
   	$: document.title = title;
   
   	$: {
   		console.log(`multiple statements can be combined`);
   		console.log(`the current title is ${title}`);
   	}
   </script>
   ```

   只有直接出现在`$:`块中的值才会成为响应式语句的依赖项。例如，在下面的代码中`total`只会在更改时更新`x`，而不是`y`.

   ```
   <script>
   	let x = 0;
   	let y = 0;
   	
   	function yPlusAValue(value) {
   		return value + y;
   	}
   	
   	$: total = yPlusAValue(x);
   </script>
   
   Total: {total}
   <button on:click={() => x++}>
   	Increment X
   </button>
   
   <button on:click={() => y++}>
   	Increment Y
   </button>
   ```

   

4. 添加前缀`$`以访问它们的值

   通过在它前面加上`$`字符来访问它在组件中的值。

   ```
   <script>
   	import { writable } from 'svelte/store';
   
   	const count = writable(0);
   	console.log($count); // logs 0
   
   	count.set(1);
   	console.log($count); // logs 1
   
   	$count = 2;
   	console.log($count); // logs 2
   </script>
   ```

   

### <脚本上下文=“模块”>

<script>具有属性的标记context="module"在模块第一次评估时运行一次，而不是针对每个组件实例。此块中声明的值可以从常规<script>（和组件标记）访问，但反之则不行。

您可以`export`从此块绑定，它们将成为已编译模块的导出。

您不能`export default`，因为默认导出是组件本身。

```
<script context="module">
	let totalComponents = 0;

	// this allows an importer to do e.g.
	// `import Example, { alertTotal } from './Example.svelte'`
	export function alertTotal() {
		alert(totalComponents);
	}
</script>

<script>
	totalComponents += 1;
	console.log(`total number of times this component has been created: ${totalComponents}`);
</script>
```

### <风格>

块内的 CSS`<style>`将作用于该组件。

这是通过向受影响的元素添加一个类来实现的，该类基于组件样式的散列（例如`svelte-123xyz`）。

```svelte
<style>
	p {
		/* this will only affect <p> elements in this component */
		color: burlywood;
	}
</style>
```

要将样式全局应用于选择器，请使用`:global(...)`修饰符。

```
<style>
	:global(body) {
		/* this will apply to <body> */
		margin: 0;
	}

	div :global(strong) {
		/* this will apply to all <strong> elements, in any
			 component, that are inside <div> elements belonging
			 to this component */
		color: goldenrod;
	}

	p:global(.red) {
		/* this will apply to all <p> elements belonging to this 
			 component with a class of red, even if class="red" does
			 not initially appear in the markup, and is instead 
			 added at runtime. This is useful when the class 
			 of the element is dynamically applied, for instance 
			 when updating the element's classList property directly. */
	}
</style>
```

