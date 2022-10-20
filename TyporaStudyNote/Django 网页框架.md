# Django 网页框架

> Django 是一个非常流行以及功能齐全的服务器端网页框架，它是用 Python 编写的。这个模块讲解了为什么 Django 是一个这么好的网页服务器框架，如何设立一个开发环境以及如何使用它来执行常见的任务。

## 1.Django 介绍

> Django 是一个高级的 Python 网络框架，可以快速开发安全和可维护的网站。由经验丰富的开发者构建，Django负责处理网站开发中麻烦的部分，因此你可以专注于编写应用程序，而无需重新开发。
> 它是免费和开源的，有活跃繁荣的社区，丰富的文档，以及很多免费和付费的解决方案。

**通用性**

Django 可以（并已经）用于构建几乎任何类型的网站—从内容管理系统和维基，到社交网络和新闻网站。它可以与任何客户端框架一起工作，并且可以提供几乎任何格式（包括 HTML，Rss源，JSON，XML等）的内容。你正在阅读的网站就是基于Django。

在内部，尽管它为几乎所有可能需要的功能（例如几个流行的数据库，模版引擎等）提供了选择，但是如果需要，它也可以扩展到使用其他组件。

**安全性**

Django 帮助开发人员通过提供一个被设计为“做正确的事情”来自动保护网站的框架来避免许多常见的安全错误。例如，Django提供了一种安全的方式来管理用户账户和密码，避免了常见的错误，比如将session放在cookie中这种易受攻击的做法（取而代之的是cookies只包含一个密钥，实际数据存储在数据库中）或直接存储密码而不是密码哈希。

可扩展

Django 使用基于组件的 “[无共享](https://en.wikipedia.org/wiki/Shared_nothing_architecture)” 架构 (架构的每一部分独立于其他架构，因此可以根据需要进行替换或更改). 在不用部分之间有明确的分隔意味着它可以通过在任何级别添加硬件来扩展服务：缓存服务器，数据库服务器或应用程序服务器。一些最繁忙的网站已经成功地缩放了Django，以满足他们的需求（例如Instagram和Disqus，仅举两个例子，可自行添加）。

可维护性

Django 代码编写是遵照设计原则和模式，鼓励创建可维护和可重复使用的代码。特别是它使用了不要重复自己（DRY）原则，所以没有不必要的重复，减少了代码的数量。Django还将相关功能分组到可重用的“应用程序”中，并且在较低级别将相关代码分组或模块（ 模型视图控制器 (MVC)模式).

灵活性

Django 是用Python编写的，它在许多平台上运行。这意味着你不受任务特定的服务器平台的限制，并且可以在许多种类的Linux，Windows和Mac OsX 上运行应用程序。此外，Django得到许多网络托管提供商的好评，他们经常提供特定的基础设施和托管Django网站的文档。

## Django 是特定?

Web框架通常将自己称为“特定”或“无限制”。

特定框架是对处理任何特定任务的“正确方法”有意见的框架。他们经常支持特定领域的快速发展（解决特定类型的问题），因为正确的做法是通常被很好地理解和记录在案。然而，他们在解决其主要领域之外的问题时可能不那么灵活，并且倾向于为可以使用哪些组件和方法提供较少的选择。

[This page was translated from English by the community. Learn more and join the MDN Web Docs community.](https://developer.mozilla.org/en-US/docs/MDN/Contribute/Localize#active_locales)



IN THIS ARTICLE[Django是什么?](https://developer.mozilla.org/zh-CN/docs/Learn/Server-side/Django/Introduction#django是什么)[它的出生?](https://developer.mozilla.org/zh-CN/docs/Learn/Server-side/Django/Introduction#它的出生)[Django有多受欢迎?](https://developer.mozilla.org/zh-CN/docs/Learn/Server-side/Django/Introduction#django有多受欢迎)[Django 是特定?](https://developer.mozilla.org/zh-CN/docs/Learn/Server-side/Django/Introduction#django_是特定)[Django代码是什么样的?](https://developer.mozilla.org/zh-CN/docs/Learn/Server-side/Django/Introduction#django代码是什么样的)[你还能做什么？](https://developer.mozilla.org/zh-CN/docs/Learn/Server-side/Django/Introduction#你还能做什么？)[概要](https://developer.mozilla.org/zh-CN/docs/Learn/Server-side/Django/Introduction#概要)

#### RELATED TOPICS

1. [**新手请从这开始！**](https://developer.mozilla.org/zh-CN/docs/Learn/Getting_started_with_the_web)
2. Web 入门
3. [**HTML — 构建 Web**](https://developer.mozilla.org/zh-CN/docs/Learn/HTML)
4. HTML 介绍
5. 多媒体与嵌入
6. HTML 表格
7. [**CSS — 设计 Web**](https://developer.mozilla.org/zh-CN/docs/Learn/CSS)
8. CSS 第一步
9. CSS 构建基础
10. 样式化文字
11. CSS 排版
12. [**JavaScript — 用户端动态脚本**](https://developer.mozilla.org/zh-CN/docs/Learn/JavaScript)
13. JavaScript 第一步
14. JavaScript 基础要件
15. JavaScript 对象介绍
16. 异步JavaScript
17. 客户端网页 API
18. [**Web表单 — 与用户数据打交道**](https://developer.mozilla.org/zh-CN/docs/Learn/Forms)
19. Web表单核心
20. Web表单进阶
21. [**可访问性 — 使每个人都能使用 Web**](https://developer.mozilla.org/zh-CN/docs/Learn/Accessibility)
22. 可访问性指南
23. 可访问性测评
24. [**工具与测试**](https://developer.mozilla.org/zh-CN/docs/Learn/Tools_and_testing)
25. 客户端web开发工具
26. 客户端框架介绍
27. React
28. Ember
29. Vue
30. Svelte
31. Angular
32. Git 和 GitHub
33. 跨浏览器测试
34. [**服务端网页编程**](https://developer.mozilla.org/zh-CN/docs/Learn/Server-side)
35. 第一步
36. Django 网站框架 (Python)
37. Express 网页框架 (node.js/JavaScript)
38. [**更多资源**](https://developer.mozilla.org/zh-CN/docs/Learn/Server-side/Django/Introduction#)
39. 常见问题

# Django 介绍

- [Overview: Django](https://developer.mozilla.org/zh-CN/docs/learn/Server-side/Django)
- [下一页](https://developer.mozilla.org/zh-CN/docs/Learn/Server-side/Django/development_environment)

在这第一Django文章中，我们将回答“什么是Django”这个问题，并概述这个网络框架有什么特性。我们将描述主要功能，包括一些高级功能，但我们并不会在本单元中详细介绍。我们还会展示一些Django应用程序的主要构建模块（尽管此时你还没有要测试的开发环境）。

| 先决条件: | 基本的电脑知识. 对 [服务器端网站编程的一般了解](https://developer.mozilla.org/en-US/docs/Learn/Server-side/First_steps), 特别是 [网站中客户端-服务器交互的机制](https://developer.mozilla.org/en-US/docs/Learn/Server-side/First_steps/Client-Server_overview). |
| :-------- | ------------------------------------------------------------ |
| 目的:     | 了解Django是什么，它提供了哪些功能，以及Django应用程序的主要构建块。 |

## [Django是什么?](https://developer.mozilla.org/zh-CN/docs/Learn/Server-side/Django/Introduction#django是什么)

Django 是一个高级的 Python 网络框架，可以快速开发安全和可维护的网站。由经验丰富的开发者构建，Django负责处理网站开发中麻烦的部分，因此你可以专注于编写应用程序，而无需重新开发。
它是免费和开源的，有活跃繁荣的社区，丰富的文档，以及很多免费和付费的解决方案。

Django 可以使你的应用具有以下优点:

- 完备性

  Django遵循“功能完备”的理念，提供开发人员可能想要“开箱即用”的几乎所有功能。因为你需要的一切都是一个”产品“的一部分，它们都可以无缝结合在一起，遵循一致性设计原则，并且具有广泛和[最新的文档](https://docs.djangoproject.com/en/1.10/).

- 通用性

  Django 可以（并已经）用于构建几乎任何类型的网站—从内容管理系统和维基，到社交网络和新闻网站。它可以与任何客户端框架一起工作，并且可以提供几乎任何格式（包括 HTML，Rss源，JSON，XML等）的内容。你正在阅读的网站就是基于Django。  在内部，尽管它为几乎所有可能需要的功能（例如几个流行的数据库，模版引擎等）提供了选择，但是如果需要，它也可以扩展到使用其他组件。

- 安全性

  Django 帮助开发人员通过提供一个被设计为“做正确的事情”来自动保护网站的框架来避免许多常见的安全错误。例如，Django提供了一种安全的方式来管理用户账户和密码，避免了常见的错误，比如将session放在cookie中这种易受攻击的做法（取而代之的是cookies只包含一个密钥，实际数据存储在数据库中）或直接存储密码而不是密码哈希。  密码哈希是通过*[密码散列函数](https://en.wikipedia.org/wiki/Cryptographic_hash_function)发送密码而创建的固定长度值。 Django 能通过运行哈希函数来检查输入的密码-就是-将输出的哈希值与存储的哈希值进行比较是否正确。然而由于功能的“单向”性质，即时存储的哈希值受到威胁，攻击者也难以解决原始密码。（但其实有彩虹表-译者观点）*  默认情况下，Django 可以防范许多漏洞，包括SQL注入，跨站点脚本，跨站点请求伪造和点击劫持 (请参阅 [网站安全](https://developer.mozilla.org/en-US/docs/Learn/Server-side/First_steps/Website_security) 相关信息，如有兴趣).

- 可扩展

  Django 使用基于组件的 “[无共享](https://en.wikipedia.org/wiki/Shared_nothing_architecture)” 架构 (架构的每一部分独立于其他架构，因此可以根据需要进行替换或更改). 在不用部分之间有明确的分隔意味着它可以通过在任何级别添加硬件来扩展服务：缓存服务器，数据库服务器或应用程序服务器。一些最繁忙的网站已经成功地缩放了Django，以满足他们的需求（例如Instagram和Disqus，仅举两个例子，可自行添加）。

- 可维护性

  Django 代码编写是遵照设计原则和模式，鼓励创建可维护和可重复使用的代码。特别是它使用了不要重复自己（DRY）原则，所以没有不必要的重复，减少了代码的数量。Django还将相关功能分组到可重用的“应用程序”中，并且在较低级别将相关代码分组或模块（ [模型视图控制器 (MVC)](https://developer.mozilla.org/en-US/docs/Web/Apps/Fundamentals/Modern_web_app_architecture/MVC_architecture) 模式).

- 灵活性

  Django 是用Python编写的，它在许多平台上运行。这意味着你不受任务特定的服务器平台的限制，并且可以在许多种类的Linux，Windows和Mac OsX 上运行应用程序。此外，Django得到许多网络托管提供商的好评，他们经常提供特定的基础设施和托管Django网站的文档。

## [它的出生?](https://developer.mozilla.org/zh-CN/docs/Learn/Server-side/Django/Introduction#它的出生)

Django 最初由2003年到2005年间由负责创建和维护报纸网站的网络团队开发。在创建了许多网站后，团队开始考虑并重用许多常见的代码和设计模式。这个共同的代码演变一个通用的网络开发框架，2005年7月被开源“Django”项目。

Django 不断发展壮大—从2008年9月的第一个里程碑版本（1.0）到最近发布的（1.11）-（2017）版本。每个版本都添加了新功能和错误修复，从支持新类型的数据库，模版引擎和缓存，到添加“通用”视图函数和类（这减少了开发人员必须编写的代码量）一些编程任务。

**注意**: 查看Django网站上 [发行说明](https://docs.djangoproject.com/en/1.10/releases/)，看看最近版本发生了什么变化，以及Django能做多少工作。

Django 现在是一个蓬勃发展的合作开源项目，拥有数千个用户和贡献着。虽然它仍然具有反映其起源的一些功能，但Django已经发展成为能够开发任何类型的网站的多功能框架。

## [Django有多受欢迎?](https://developer.mozilla.org/zh-CN/docs/Learn/Server-side/Django/Introduction#django有多受欢迎)

服务器端框架的受欢迎程度没有任何可靠和明确的测量（尽管[Hot Frameworks](http://hotframeworks.com/)网站 尝试使用诸如计算每个平台的GitHub项目数量和StackOverflow问题的机制来评估流行度）。一个更好的问题是Django是否“足够流行”，以避免不受欢迎的平台的问题。它是否继续发展？如果您需要帮助，可以帮您吗？如果您学习Django，有机会获得付费工作吗？

基于使用Django的流行网站数量，为代码库贡献的人数以及提供免费和付费支持的人数，那么是的，Django是一个流行的框架！

使用Django的流行网站包括：Disqus，Instagram，骑士基金会，麦克阿瑟基金会，Mozilla，国家地理，开放知识基金会，Pinterest和开放栈（来源：[Django home page](https://www.djangoproject.com/)).

## [Django 是特定?

Web框架通常将自己称为“特定”或“无限制”。

特定框架是对处理任何特定任务的“正确方法”有意见的框架。他们经常支持特定领域的快速发展（解决特定类型的问题），因为正确的做法是通常被很好地理解和记录在案。然而，他们在解决其主要领域之外的问题时可能不那么灵活，并且倾向于为可以使用哪些组件和方法提供较少的选择。

相比之下，无限制的框架对于将组件粘合在一起以实现目标或甚至应使用哪些组件的最佳方式的限制较少。它们使开发人员更容易使用最合适的工具来完成特定任务，尽管您需要自己查找这些组件。

Django“有点有意义”，因此提供了“两个世界的最佳”。它提供了一组组件来处理大多数Web开发任务和一个（或两个）首选的使用方法。然而，Django的解耦架构意味着您通常可以从多个不同的选项中进行选择，也可以根据需要添加对全新的支持。

## [Django代码是什么样的?

在传统的数据驱动网站中，Web应用程序会等待来自Web浏览器（或其他客户端）的 HTTP 请求。当接收到请求时，应用程序根据 URL 和可能的 POST 数据或 GET 数据中的信息确定需要的内容。根据需要，可以从数据库读取或写入信息，或执行满足请求所需的其他任务。然后，该应用程序将返回对Web浏览器的响应，通常通过将**检索到的数据插入 HTML模板中的占位符**来动态创建用于浏览器显示的 HTML 页面。![img](https://mdn.mozillademos.org/files/13931/basic-django.png)

- **URLs:**虽然可以通过单个功能来处理来自每个URL的请求，但是编写单独的视图函数来处理每个资源是更加可维护的。URL映射器用于根据请求URL将HTTP请求重定向到相应的视图。URL映射器还可以匹配出现在URL中的字符串或数字的特定模式，并将其作为数据传递给视图功能。
- **View:** 视图 是一个请求处理函数，它接收HTTP请求并返回HTTP响应。视图通过模型访问满足请求所需的数据，并将响应的格式委托给 模板。
- **Models:** 模型 是定义应用程序数据结构的Python对象，并提供在数据库中管理（添加，修改，删除）和查询记录的机制。
- **Templates:** 模板 是定义文件（例如HTML页面）的结构或布局的文本文件，用于表示实际内容的占位符。一个视图可以使用HTML模板，从数据填充它动态地创建一个HTML页面模型。可以使用模板来定义任何类型的文件的结构; 它不一定是HTML！

## Django的运作

#### 1>将请求发送到正确的视图 

URL映射器通常存储在名为urls.py的文件中。在下面的示例中，mapper（urlpatterns）定义了特定URL 模式 和相应视图函数之间的映射列表。如果接收到具有与指定模式匹配的URL（例如r'^$'，下面）的HTTP请求，则将调用 相关联的视图功能（例如 views.index）并传递请求。

```
urlpatterns = [
    url(r'^$', views.index),
    url(r'^([0-9]+)/$', views.best),
]

该 urlpatterns 对象的列表url() 功能。在Python中，使用方括号定义列表。项目以逗号分隔，并可能有一个 可选的逗号. 例如: [item1, item2, item3,].
该模式的奇怪的语法称为正则表达式。

第二个参数 url() 是当模式匹配时，将被调用的另一个函数。符号views.index 表示该函数被调用，index()并且可以在被调用的模块中找到views （即在一个名为views.py的文件中）。
```



#### 2>处理请求 (views.py)

视图是Web应用程序的核心，从Web客户端接收HTTP请求并返回HTTP响应。在两者之间，他们编制框架的其他资源来访问数据库，渲染模板等。

下面的例子显示了一个最小的视图功能index()，这可以通过我们的URL映射器在上一节中调用。像所有视图函数一样，它接收一个`HttpRequest`对象作为参数（request）并返回一`HttpResponse`对象。在这种情况下，我们对请求不做任何事情，我们的响应只是返回一个硬编码的字符串。

```
## filename: views.py (Django view functions)

from django.http import HttpResponse

def index(request):
    # Get an HttpRequest - the request parameter
    # perform operations using information from the request.
    # Return HttpResponse
    return HttpResponse('Hello from Django!')
    
   	Python 模块 是函数的“库”，存储在单独的文件中，我们可能想在我们的代码中使用它们。在这里我们只从django.http模块导入了HttpResponse对象，使我们可以在视图中使用它：
from django.http import HttpResponse。
	还有其他方法可以从模块导入一些或所有对象。
如上所示，使用def关键字声明函数，在函数名称后面的括号中列出命名参数；整行以冒号结尾。注意下一行是否都进行了缩进。缩进很重要，因为它指定代码行在该特定块内 (强制缩进是Python的一个关键特征，也是Python代码很容易阅读的一个原因)。
```

#### 3> 定义数据模型 (models.py)

> Django Web应用程序通过被称为模型的Python对象来管理和查询数据。

**也就是通过这个model来管理数据**

模型定义存储数据的结构，包括字段类型 以及字段可能的最大值，默认值，选择列表选项，文档帮助文本，表单的标签文本等。**模型的定义与底层数据库无关 -您可以选择其中一个作为项目设置的一部分**。一旦您选择了要使用的数据库，您就不需要直接与之交谈 - 只需编写模型结构和其他代码，**Django可以处理与数据库通信的所有辛苦的工作。**

下面的代码片段为**Team**对象展示了一个非常简单的Django模型。本**Team**类是从Django的类**models.Model**派生。它将团队名称和团队级别定义为字符字段，并为每个记录指定了要存储的最大字符数。**team_level** 可以是几个值中的一个，因此，我们将其定义为一个选择字段，并在**被展示的数据和被储存的数据之间建立映射，并设置一个默认值**。

```
# filename: models.py

from django.db import models

class Team(models.Model):
    team_name = models.CharField(max_length=40)

    TEAM_LEVELS = (
        ('U09', 'Under 09s'),
        ('U10', 'Under 10s'),
        ('U11', 'Under 11s'),
        ...  #list other team levels
    )
    team_level = models.CharField(max_length=3,choices=TEAM_LEVELS,default='U11')
```

```
Python小知识:

Python支持“面向对象编程”，这是一种编程风格，我们将代码组织到对象中，其中包括用于对该对象进行操作的相关数据和功能。对象也可以从其他对象继承／扩展／派生，允许相关对象之间的共同行为被共享。在Python中，我们使用关键字 Class 定义对象的“蓝图”。我们可以根据类中的模型创建类型的多个 特定 实例。

例如，我们有个 Team 类，它来自于Model类。这意味着它是一个模型，并且将包含模型的所有方法，但是我们也可以给它自己的专门功能。在我们的模型中，我们定义了我们的数据库需要存储我们的数据字段，给出它们的具体名称。Django使用这些定义（包括字段名称）来创建底层数据库。
```

#### 4> 查询数据 (views.py)

```
代码片段显示了一个视图函数（资源处理程序），用于显示我们所有的 U09 团队。粗体显示如何使用模型查询API过滤所有记录，其中该  team_level 字段具有正确的文本“U09”（请注意，该条件如何filter()作为参数传递给该函数，该字段名称和匹配类型由双下划线：  team_level__exact）## filename: views.py

from django.shortcuts import render
from .models import Team

def index(request):
    list_teams = Team.objects.filter(team_level__exact="U09")
    context = {'youngest_teams': list_teams}
    return render(request, '/best/index.html', context)
```

此功能使用 **render**() 功能创建 **HttpResponse** 发送回浏览器的功能。这个函数是一个快捷方式；它通过组合**指定的HTML模版和一些数据**来插入模版（在名为 “**context**” 的变量中提供）来创建一个**HTML**文件。在下一节中，我们将介绍如何在其中插入数据以创建**HTML**。

- **把查找到的数据或者说是--过滤好的数据与我们最终想要呈现的和数据组合为一个变量，然后把数据插入到模板中。**

#### 5> 呈现数据 (HTML 模版)

模版系统允许你指定输出文档的结构，使用

```
占位符
{% if youngest_teams%}
来生成页面时填写的数据。
```

模版通常用于创建HTMl，但也可以创建其他类型的文档。Django支持其原生模版系统和另一种流行的Python库（称为jinja2）开箱即用（如果需要，也可以支持其他系统）。

代码片段显示render()了上一节中函数调用的HTML模版的外观。这个模版已经被写入这样的想法，即它将被访问一个列表变量，
youngest_teams当它被渲染时

```
## filename: best/templates/best/index.html

<!DOCTYPE html>
<html lang="en">
<body>

 {% if youngest_teams %}
    <ul>
    {% for team in youngest_teams %}
        <li>{{ team.team_name }}</li>
    {% endfor %}
    </ul>
{% else %}
    <p>No teams are available.</p>
{% endif %}

</body>
</html>
```

#### > 还能做什么？

- **表单**: HTML 表单用于收集用户数据以便在服务器上进行处理。Django简化了表单创建，验证和处理。
- **用户身份验证和权限**: Django包含了一个强大的用户身份验证和权限系统，该系统已经构建了安全性。
- **缓存**: 与提供静态内容相比，动态创建内容需要更大的计算强度（也更缓慢）。Django提供灵活的缓存，以便你可以存储所有或部分的页面。如无必要，不会重新呈现网页。
- **管理网站**: 当你使用基本骨架创建应用时，就已经默认包含了一个Django管理站点。它十分轻松地创建了一个管理页面，使网站管理员能够创建、编辑和查看站点中的任何数据模型。
- **序列化数据**: Django可以轻松地将数据序列化，并支持XML或JSON格式。这会有助于创建一个Web服务（Web服务指数据纯粹为其他应用程序或站点所用，并不会在自己的站点中显示），或是有助于创建一个由客户端代码处理和呈现所有数据的网站。