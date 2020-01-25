(window.webpackJsonp=window.webpackJsonp||[]).push([[27],{"+GB+":function(module,e,t){"use strict";t.r(e);var n=t("VbXa"),a=t.n(n),r=t("sbe7"),i=t.n(r),o=t("KMW/"),s=t("wiyT"),u=t.n(s),c=t("H1EP"),d=t("8WNh"),l=t("X6TH"),m=t("jYVy"),g=t("k6K2"),p=t("LsRy"),h=t("rerG"),f=t("+9K8"),k=function(e){function ProgrammingInstructions(){for(var t,n=arguments.length,a=new Array(n),r=0;r<n;r++)a[r]=arguments[r];return(t=e.call.apply(e,[this].concat(a))||this).state={isLoaded:!1,instructions:null,learnerAssignment:null,labLauncher:null},t}a()(ProgrammingInstructions,e);var t=ProgrammingInstructions.prototype;return t.componentDidMount=function componentDidMount(){this.fetchData()},t.fetchData=function fetchData(){var e=this,t=this.props.itemMetadata,n=t.get("id"),a=t.get("course.id");if("programming"===t.getTypeName()){var r=Object(l.a)({itemMetadata:t,courseId:a,itemId:n});u()(r).then(function(t){e.setState({isLoaded:!0,instructions:t})})}else{var i=Object(m.a)({itemId:n,courseId:a,courseSlug:t.get("course.slug")});u()(i).then(function(t){var r;return"workspace"===t.submissionBuilderSchema.get("typeName")?Object(h.b)(a,n).then(function(n){e.setState({isLoaded:!0,instructions:t.submissionLearnerSchema.get("instructions"),learnerAssignment:t,labLauncher:n})}):u()().then(function(){e.setState({isLoaded:!0,instructions:t.submissionLearnerSchema.get("instructions"),learnerAssignment:t})})}).done()}},t.render=function render(){var e=this.props.itemMetadata,t=this.state,n=t.isLoaded,a=t.instructions,r=t.learnerAssignment,s=t.labLauncher,u={itemMetadata:e,instructions:a,learnerAssignment:r,labLauncher:s},l=o.a.get("programming","isReactViewsEnabled");return i.a.createElement("div",{className:"rc-ProgrammingInstructions"},!n&&i.a.createElement(d.a,null),n&&!l&&i.a.createElement(c.a,{viewOptions:u,ViewClass:p.a,renderOnce:!0}),n&&l&&i.a.createElement(g.a,{instructions:a,itemMetadata:e,labLauncher:s,learnerAssignment:r}))},ProgrammingInstructions}(r.Component);e.default=Object(f.a)(k)},"/zPY":function(module,exports,e){var t=e("kp6c"),n;"string"==typeof t&&(t=[[module.i,t,""]]);var a={transform:void 0},r=e("aET+")(t,a);t.locals&&(module.exports=t.locals)},"1vPD":function(module,e,t){"use strict";var n=t("VbXa"),a=t.n(n),r=t("sbe7"),i=t.n(r),o=t("sQ/U"),s=t("BBzL"),u=t.n(s),c=t("4+Xa"),d=function(e){function TokenBox(){for(var t,n=arguments.length,a=new Array(n),r=0;r<n;r++)a[r]=arguments[r];return(t=e.call.apply(e,[this].concat(a))||this).state={secret:"",status:"empty"},t.handleClickGenerateToken=function(e){e.preventDefault(),t.generateToken()},t.handleClickGetToken=function(e){e.preventDefault(),t.getToken()},t}a()(TokenBox,e);var t=TokenBox.prototype;return t.componentDidMount=function componentDidMount(){this.getToken()},t.getToken=function getToken(){var e=this,t=this.props.itemMetadata;return this.setState({status:"getting"}),c.a.get({itemId:t.get("id"),courseId:t.get("course.id"),courseSlug:t.get("course.slug")}).then(function(t){var n=t.elements[0];e.setState({secret:n.token||n.secret,status:"displaying"})},function(t){return 404===t.status?e.generateToken():e.setState({status:"error"})}).done()},t.generateToken=function generateToken(){var e=this,t=this.props.itemMetadata;return this.setState({status:"generating"}),c.a.newToken({itemId:t.get("id"),courseId:t.get("course.id"),courseSlug:t.get("course.slug")}).then(function(t){var n=t.body.elements[0];e.setState({secret:n.token||n.secret,status:"displaying"})}).done()},t.render=function render(){var e=this.state,t=e.secret,n=e.status;return i.a.createElement("div",{className:"rc-TokenBox well"},i.a.createElement("h5",{className:"headline-2-text"},u()("How to submit")),i.a.createElement("p",null,u()("Copy the token below and run the submission script included in the assignment download. When prompted, use your email address "),i.a.createElement("b",null,o.a.get().email_address),"."),i.a.createElement("div",{className:"token-generator bt3-text-center"},"empty"===n&&i.a.createElement("p",null,u()("no token")),"getting"===n&&i.a.createElement("p",null,u()("Getting token...")),"generating"===n&&i.a.createElement("p",null,u()("Generating token...")),"displaying"===n&&i.a.createElement("div",null,i.a.createElement("h5",{className:"headline-2-text","data-js":"secret"},t),i.a.createElement("p",null,i.a.createElement("button",{type:"button",onClick:this.handleClickGenerateToken},u()("Generate new token")))),"error"===n&&i.a.createElement("div",null,i.a.createElement("p",null,u()("There was an error getting your token:")),i.a.createElement("button",{type:"button",onClick:this.handleClickGetToken},u()("Click here to try to get it again")))),i.a.createElement("p",null,u()("Your submission token is unique to you and should not be shared with anyone. You may submit as many times as you like.")))},TokenBox}(i.a.Component);e.a=d},"4+Xa":function(module,e,t){"use strict";var n=t("eBhw"),a="onDemandProgrammingTokens.v1",r={get:function get(e){var t=e.itemId,r=e.courseId,i=e.courseSlug,o;return new n.a({itemId:t,courseId:r,courseSlug:i}).getWithCourseItemId(a)},newToken:function newToken(e){var t=e.itemId,r=e.courseId,i=e.courseSlug,o,s=null,u={courseId:r,itemId:t};return new n.a({itemId:t,courseId:r,courseSlug:i}).create(a,u,null,!1)}};e.a=r;var i=r.get,o=r.newToken},"4b+W":function(module,e,t){"use strict";var n=t("PDuk"),a=t.n(n),r=t("BDKN"),i=t.n(r),o=t("LeYt");e.a=function(e){var t=e.courseId,n=e.itemId,r=a.a.tupleToStringKey([t,n]),s=new i.a(r);return o.a.get(s.toString())}},"52k5":function(module,e,t){"use strict";var n=t("VbXa"),a=t.n(n),r=t("bdFs"),i=t.n(r),o=t("sbe7"),s=t.n(o),u=t("17x9"),c=t.n(u),d=t("VYij"),l=t.n(d),m=t("CA+Q"),g=t("+2ZD"),p=t("sQ/U"),h=t("F9Z8"),f=t("PUBa"),k=t("hidG"),v=t("kvW3"),b=t("BBzL"),T=t.n(b),y=t("LMJJ"),w=t("OAHX"),I=t("tOcQ"),E=t.n(I),S=t("hOpA"),M=t.n(S),x={gradedProgramming:y.a,ungradedProgramming:w.a},C=function(e){function ScriptTokenBox(){for(var t,n=arguments.length,a=new Array(n),r=0;r<n;r++)a[r]=arguments[r];return(t=e.call.apply(e,[this].concat(a))||this).state={agreementComplete:!1,currentTime:Date.now(),error:null,fullName:"",generatingToken:!1,isVerifying:!1,state:"ready",token:{}},t.onSubmitHonorCodeAgreement=function(){var e=t.state.fullName;t.setState({generatingToken:!0}),Object(f.a)().then(function(n){Object(f.b)(n,e).then(function(e){t.generateToken(e.get("id")),t.setState({isVerifying:!1,generatingToken:!1,agreementComplete:!1})})})},t.onTokenNotFound=function(){t.isGraded()?t.setState({state:"displaying"}):t.generateToken()},t.onTokenGenerated=function(){t.loadToken()},t.onFailedTokenGeneration=function(e){t.setState({state:"error",error:e})},t.onVerificationModalClose=function(){t.setState({isVerifying:!1})},t.onReceiveToken=function(e){t.setState({state:"displaying",token:e})},t.onHonorCodeAgreementComplete=function(e){t.setState({agreementComplete:!0,fullName:e})},t.onHonorCodeAgreementIncomplete=function(){t.setState({agreementComplete:!1})},t.updateCurrentTime=function(){t.setState({currentTime:Date.now()})},t.verifyAndGenerateToken=function(e){e&&e.preventDefault(),t.isGraded()?t.setState({isVerifying:!0}):t.generateToken()},t.api={},t.currentTimeInterval=null,t}a()(ScriptTokenBox,e);var t=ScriptTokenBox.prototype;return t.componentDidMount=function componentDidMount(){var e,t=this.props.itemMetadata.getTypeName();this.api=x[t],Object(k.a)(this.api,"Unknown assignment type: "+t),this.currentTimeInterval=window.setInterval(this.updateCurrentTime,1e3),this.loadToken()},t.componentWillUnmount=function componentWillUnmount(){this.currentTimeInterval&&clearInterval(this.currentTimeInterval)},t.loadToken=function loadToken(){this.setState({state:"getting"});var e=this.props.itemMetadata,t=e.get("id"),n=e.get("course").get("id"),a=e.get("course").get("slug");this.api.get({itemId:t,courseId:n,courseSlug:a}).then(m.a).then(function(e){return e.elements[0]}).then(this.onReceiveToken,this.onTokenNotFound).done()},t.generateToken=function generateToken(e){this.setState({state:"generating"});var t=this.props.itemMetadata,n=t.get("id"),a=t.get("course").get("id"),r=t.get("course").get("slug");this.api.newToken({itemId:n,courseId:a,courseSlug:r,verifiableId:e}).then(this.onTokenGenerated,this.onFailedTokenGeneration)},t.isGraded=function isGraded(){var e;return"gradedProgramming"===this.props.itemMetadata.getTypeName()},t.render=function render(){var e=this.state,t=e.state,n=e.token,a=e.currentTime,r=e.isVerifying,o=e.error,u=e.agreementComplete,c=e.generatingToken,d=n&&n.expiresAt-a<=0;return s.a.createElement("div",{className:"rc-ScriptTokenBox well card-rich-interaction"},s.a.createElement("h3",{className:"head-2-text"},T()("How to submit")),s.a.createElement("p",null,s.a.createElement(v.b,{message:"Copy the token below and run the submission script included in the assignment download. When prompted, use your email address {userEmailAddress}.",userEmailAddress:s.a.createElement("b",null,p.a.get().email_address)})),s.a.createElement("div",{className:"token-area bt3-text-center"},l()(["getting","generating"]).contains(t)&&s.a.createElement("p",null,T()("Loading token...")),l()(["displaying"]).contains(t)&&s.a.createElement("div",null,n&&s.a.createElement("div",null,(!n.expiresAt||!d)&&s.a.createElement("h4",null,n.secret),n.expiresAt&&!d&&s.a.createElement("p",{className:"caption-text"},s.a.createElement(v.b,{message:T()("This token expires in {expirationTime}"),expirationTime:i()(n.expiresAt).fromNow(!0)})),n.expiresAt&&d&&s.a.createElement("p",{className:"caption-text"},T()("Your token expired"))),s.a.createElement("p",null,s.a.createElement("button",{className:"button-link",type:"button",onClick:this.verifyAndGenerateToken},T()("Generate new token")))),l()(["error"]).contains(t)&&s.a.createElement("div",null,s.a.createElement("p",null,s.a.createElement(v.b,{message:T()("There was an error getting your token: {error}"),error:o})," ",s.a.createElement("button",{className:"button-link",type:"button",onClick:this.verifyAndGenerateToken},T()("Click here to try to get it again"))))),s.a.createElement("p",null,T()("Your submission token is unique to you and should not be shared with anyone.\n          You may submit as many times as you like.")),r&&s.a.createElement(g.a,{className:"honor-code-modal",modalName:"Programming Assignment Token",handleClose:this.onVerificationModalClose},s.a.createElement("h2",{className:"head-2-text"},T()("Honor Code")),s.a.createElement(h.a,{onAgreementComplete:this.onHonorCodeAgreementComplete,onAgreementIncomplete:this.onHonorCodeAgreementIncomplete,isShownInsideModal:!0}),s.a.createElement("div",{className:"align-right"},s.a.createElement("button",{className:"agreement-continue-button primary",type:"button",disabled:!u||c,onClick:this.onSubmitHonorCodeAgreement},c?T()("Loading..."):T()("Continue")))))},ScriptTokenBox}(s.a.Component);C.contextTypes={fluxibleContext:c.a.object.isRequired},e.a=C},"6yWA":function(module,exports,e){},"7FO1":function(module,e,t){"use strict";var n=t("VbXa"),a=t.n(n),r=t("sbe7"),i=t.n(r),o=t("sQ/U"),s=t("7mPg"),u=t("6aOg"),c=t("BBzL"),d=t.n(c),l=function(e){function SleuthWorkspaceButton(){for(var t,n=arguments.length,a=new Array(n),r=0;r<n;r++)a[r]=arguments[r];return(t=e.call.apply(e,[this].concat(a))||this).getLaunchUrl=function(){var e=t.props,n=e.templateId,a=e.itemId,r=o.a.get().id;return t.workspacePromise||(t.workspacePromise=Object(s.a)(r,n)),t.workspacePromise.then(function(e){var t=e.id;return Object(s.b)(t,a)}).then(function(e){return e.url})},t.workspacePromise=void 0,t}var t;return a()(SleuthWorkspaceButton,e),SleuthWorkspaceButton.prototype.render=function render(){return i.a.createElement(u.a,{appName:d()("Sleuth Game"),getLaunchUrl:this.getLaunchUrl})},SleuthWorkspaceButton}(r.Component);e.a=l},"7mPg":function(module,e,t){"use strict";t.d(e,"a",function(){return h}),t.d(e,"b",function(){return f});var n=t("wiyT"),a=t.n(n),r=t("BDKN"),i=t.n(r),o=t("DnuM"),s=t("sQ/U"),u=t("PDuk"),c=t.n(u),d=Object(o.a)("/api/workspaceMetadata.v1",{type:"rest"}),l=Object(o.a)("/api/workspaceLaunch.v1",{type:"rest"}),m=function checkedPromise(e){return a()(e).done(),e},g=function getWorkspace(e,t){var n=(new i.a).addQueryParam("q","user").addQueryParam("userId",String(e)).addQueryParam("templateId",t);return m(d.get(n.toString()).then(function(e){return e&&e.elements&&e.elements[0]}))},p=function createWorkspace(e,t){var n=new i.a,a={templateId:t,owners:[e],publishDestinations:[]};return m(d.post(n.toString(),{data:a}).then(function(e){return e&&e.elements&&e.elements[0]}))},h=function getOrCreateWorkspace(e,t){return m(g(e,t).then(function(n){return n||p(e,t)}))},f=function getWorkspaceLaunchUrl(e,t){var n=Object(u.tupleToStringKey)([s.a.get().id,e]),a=(new i.a).addQueryParam("action","launch").addQueryParam("userWorkspaceId",n).addQueryParam("itemId",t);return m(l.post(a.toString()))}},"8ekE":function(module,e,t){"use strict";var n=t("oYk5"),a=t.n(n),r=t("sbe7"),i=t.n(r),o=t("i8i4"),s=t.n(o),u=t("VYij"),c=t.n(u),d=t("JUgE");function renderContentPrivateImplementation(e,t,n,r){var o=a()(t);n=n||{},e?"cml"===e.typeName?o[0]?s.a.render(i.a.createElement(d.a,c()(n).extend({cml:e})),o[0]):console.error('renderContentPrivateImplementation received an empty element set for selector "'+o.selector+'" and cannot render.'):"htmlText"===e.typeName?o.html(e.definition.content):r?o.html(e):o.text(e):o.html("")}e.a=renderContentPrivateImplementation},"9PV7":function(module,e,t){"use strict";var n=t("VYij"),a=t.n(n),r=t("8ekE");e.a=a()(r.a).partial(a.a,a.a,a.a,!0)},CvTo:function(module,e,t){"use strict";var n=t("VYij"),a=t.n(n),r=t("G5Va"),i=t("sQ/U"),o=t("gVxV"),s=t("FByn"),u=t.n(s),c=t("/zPY"),d=t.n(c),l=r.a.extend({template:u.a,stateModelProperty:"viewModel",events:{'click [data-js="generate-token"]':"generateToken",'click [data-js="get-token"]':"getToken"},templateOptions:function templateOptions(){return{userEmail:i.a.get().email_address}},initialize:function initialize(e){a()(this).extend(a()(e).pick("itemMetadata")),this.viewModel=new o.a({},{itemMetadata:this.itemMetadata}),this.viewModel.getToken(),this.listenTo(this.viewModel,"change:secret",this.renderTokenValue)},postRender:function postRender(){this.renderTokenValue()},renderTokenValue:function renderTokenValue(){this.$$("secret").text(this.viewModel.get("secret"))},generateToken:function generateToken(e){e.preventDefault(),this.viewModel.generateToken()},getToken:function getToken(e){e.preventDefault(),this.viewModel.getToken()}});e.a=l},FByn:function(module,exports,e){var t,n,a,r;a=window,r=function(e,t,n){var a=function template(t){var n=[],a,r=t||{};return function(t){n.push('<div class="rc-TokenBox well"><h5 class="headline-2-text">How to submit</h5><p>Copy the token below and run the submission script included in the assignment download.\nWhen prompted, use your email address <b>'+e.escape(null==(a=t)?"":a)+'</b>.\n</p><div class="token-generator bt3-text-center"><div data-state="getting generating"><p>Loading token...</p></div><div data-state="displaying"><h5 data-js="secret" class="headline-2-text"></h5><p><a data-js="generate-token" href="#">Generate new token</a></p></div><div data-state="error"><p>There was an error getting your token:&nbsp;<a data-js="get-token" href="#">Click here to try to get it again</a></p></div></div><p>Your submission token is unique to you and should not be shared with anyone.\nYou may submit as many times as you like.</p></div>')}.call(this,"userEmail"in r?r.userEmail:"undefined"!=typeof userEmail?userEmail:void 0),n.join("")};return function(e){return e&&"_t"in e&&(t=e._t.merge(t)),a(e)}},t=[e("xgPa"),e("HgtO")],void 0===(n=function(e,t){var n;return r(e,t,n)}.apply(exports,t))||(module.exports=n)},HgtO:function(module,exports,e){var t=e("KTHm"),n=t.default?t.default:{},a,r=(0,e("HdzH").default)(n);r.getLocale=function(){return"ru"},module.exports=r},JhhW:function(module,exports,e){var t=e("skzQ"),n=t.default?t.default:{},a,r=(0,e("HdzH").default)(n);r.getLocale=function(){return"ru"},module.exports=r},KTHm:function(module,exports){exports.default={"Click here to try to get it again":"Нажмите сюда, чтобы попробовать получить его еще раз.","Copy the token below and run the submission script included in the assignment download.":"Скопируйте указанный ниже маркер и запустите сценарий отправки работы из пакета загрузки.","Generate new token":"Сгенерировать новый маркер","How to submit":"Как отправить","Loading token...":"Загрузка маркера…","There was an error getting your token:&nbsp;":"Не удалось получить маркер: ","When prompted, use your email address <b>#{userEmail}</b>.":"Когда появится запрос, введите электронный адрес <b>#{userEmail}</b>.","You may submit as many times as you like.":"Количество сдач не ограничено.","Your submission token is unique to you and should not be shared with anyone.":"Маркер работы предназначен только для вас, не передавайте его никому."}},LMJJ:function(module,e,t){"use strict";var n=t("sQ/U"),a=t("eBhw"),r="onDemandProgrammingGradedScriptTokens.v1",i={get:function get(e){var t=e.itemId,n=e.courseId,i=e.courseSlug,o;return new a.a({itemId:t,courseId:n,courseSlug:i}).getWithUserCourseItemId(r,{fields:["secret","issuedTo","issuedAt","expiresAt"]})},newToken:function newToken(e){var t=e.itemId,i=e.courseId,o=e.courseSlug,s=e.verifiableId,u=new a.a({itemId:t,courseId:i,courseSlug:o}),c=null,d={courseId:i,itemId:t,learnerId:n.a.get().id,verifiableId:s||null};return u.create(r,d,null,!1)}};e.a=i;var o=i.get,s=i.newToken},LeYt:function(module,e,t){"use strict";var n=t("CWYE");e.a=Object(n.a)("/api/onDemandProgrammingImmediateInstructions.v1/",{type:"rest"})},LsRy:function(module,e,t){"use strict";var n=t("VYij"),a=t.n(n),r=t("1V7Y"),i=t("cwew"),o=t("9PV7"),s=t("G5Va"),u=t("52k5"),c=t("CvTo"),d=t("NRTn"),l=t.n(d),m=t("uMx8"),g=t("7FO1"),p=s.a.extend({name:"body",template:l.a,multitracker:{namespace:"open_course_item.programing_instructions",baseValues:["open_course_id","module_id","lesson_id","item_id"],definitions:{open_course_id:i.a.metadata("course.id"),module_id:i.a.metadata("lesson.module.id"),lesson_id:i.a.metadata("lesson.id"),item_id:i.a.metadata("id")},events:{render:[]}},initialize:function initialize(e){a()(this).extend(a()(e).pick("instructions","itemMetadata","learnerAssignment","labLauncher")),r.a.setMetatags({pageName:"title-and-description",context:{title:this.itemMetadata.getName(),description:this.itemMetadata.get("lesson.module.description")}})},templateOptions:function templateOptions(){return this.isPremiumGrading=this.itemMetadata.isPremiumGradingLocked(),{isPremiumGrading:this.isPremiumGrading}},postRender:function postRender(){this.track("render")},renderSubviews:function renderSubviews(){switch(this.renderReactViews(),this.itemMetadata.getTypeName()){case"programming":this.region.append(c.a,{to:this.$$("token-box"),initialize:{itemMetadata:this.itemMetadata},module:c.a});break;case"gradedProgramming":case"ungradedProgramming":var e,t=Object(m.b)(this.itemMetadata.get("course.id"),this.itemMetadata.get("id"))||this.labLauncher;"script"===this.learnerAssignment.submissionBuilderSchema.get("typeName")?this.renderReactIntoElement(u.a,this.$$("token-box")[0],{itemMetadata:this.itemMetadata}):t||this.$$("how-to-submit").removeClass("bt3-hide")}},renderReactViews:function renderReactViews(){this.instructions&&Object(o.a)(this.instructions.get("assignmentInstructions"),this.$$("instructions")),this.renderWorkspaceButtons()},renderWorkspaceButtons:function renderWorkspaceButtons(){var e=this.$$("workspace-button")[0],t=this.itemMetadata.get("course.id"),n=this.itemMetadata.get("id"),a=Object(m.a)(t,n);a&&this.renderReactIntoElement(g.a,e,{itemMetadata:this.itemMetadata,templateId:a.templateId,itemId:n})}});e.a=p},NRTn:function(module,exports,e){var t,n,a,r;a=window,r=function(e,t,n){var a=function template(e){var t=[],n;return t.push('<div class="c-programming-instructions bt3-row"><div class="bt3-col-md-8"><div data-js="instructions" class="c-programming-instructions-content"></div></div><div class="bt3-col-md-4"><div data-js="workspace-button"></div><div data-js="token-box"></div><div data-js="how-to-submit" class="bt3-hide well theme-light"><h3 class="c-title">How to submit</h3><p>When you\'re ready to submit, you can upload files for each part\nof the assignment on the "My submission" tab.</p></div></div></div>'),t.join("")};return function(e){return e&&"_t"in e&&(t=e._t.merge(t)),a(e)}},t=[e("xgPa"),e("JhhW")],void 0===(n=function(e,t){var n;return r(e,t,n)}.apply(exports,t))||(module.exports=n)},OAHX:function(module,e,t){"use strict";var n=t("sQ/U"),a=t("eBhw"),r="onDemandProgrammingUngradedScriptTokens.v1",i={get:function get(e){var t=e.itemId,n=e.courseId,i=e.courseSlug,o;return new a.a({itemId:t,courseId:n,courseSlug:i}).getWithUserCourseItemId(r,{fields:["secret","issuedTo","issuedAt","expiresAt"]})},newToken:function newToken(e){var t=e.itemId,i=e.courseId,o=e.courseSlug,s=new a.a({itemId:t,courseId:i,courseSlug:o}),u=null,c={courseId:i,itemId:t,learnerId:n.a.get().id};return s.create(r,c,null,!1)}};e.a=i;var o=i.get,s=i.newToken},X6TH:function(module,e,t){"use strict";var n=t("wiyT"),a=t.n(n),r=t("CA+Q"),i=t("sQ/U"),o=t("4b+W"),s=t("/KA1");e.a=function(e){return i.a.isAuthenticatedUser()?Object(o.a)(e).then(r.a).then(function(e){var t=e.elements[0];return new s.a(t,{parse:!0})}):a()({})}},cwew:function(module,e,t){"use strict";var n=t("VYij"),a=t.n(n),r=t("YCpq"),i={metadata:function metadata(e,t){return t=t||"itemMetadata",function(){return this[t].get(e)}},user:{id:function id(){return r.a.get("id")}}};e.a=i;var o=i.metadata,s=i.user},gVxV:function(module,e,t){"use strict";var n=t("VYij"),a=t.n(n),r=t("uUkQ"),i=t("4+Xa"),o=r.a.extend({defaults:{state:"empty",secret:null},fsm:{states:["empty","getting","displaying","generating","error"],transitions:{displaying:["getting","generating"],generating:["getting","displaying"],error:["getting","generating"]}},initialize:function initialize(e,t){a()(this).bindAll("onGenerateSuccess","onGenerateFailure","onGetSuccess","onGetFailure"),a()(this).extend(a()(t).pick("itemMetadata"))},_generateToken:function _generateToken(){return this.transition("generating"),i.a.newToken({itemId:this.itemMetadata.get("id"),courseId:this.itemMetadata.get("course.id"),courseSlug:this.itemMetadata.get("course.slug")}).then(this.onGenerateSuccess,this.onGenerateFailure)},generateToken:function generateToken(){this._generateToken().done()},getToken:function getToken(){this.transition("getting"),i.a.get({itemId:this.itemMetadata.get("id"),courseId:this.itemMetadata.get("course.id"),courseSlug:this.itemMetadata.get("course.slug")}).then(this.onGetSuccess,this.onGetFailure).done()},onGenerateSuccess:function onGenerateSuccess(e){var t=e.body.elements[0];this.transition("displaying",{secret:t.token||t.secret})},onGenerateFailure:function onGenerateFailure(e){throw this.transition("error"),e},onGetSuccess:function onGetSuccess(e){var t=e.elements[0];this.transition("displaying",{secret:t.token||t.secret})},onGetFailure:function onGetFailure(e){if(404===e.status)return this._generateToken();throw this.transition("error"),e}});e.a=o},hOpA:function(module,exports,e){var t=e("6yWA"),n;"string"==typeof t&&(t=[[module.i,t,""]]);var a={transform:void 0},r=e("aET+")(t,a);t.locals&&(module.exports=t.locals)},k6K2:function(module,e,t){"use strict";var n=t("VbXa"),a=t.n(n),r=t("sbe7"),i=t.n(r),o=t("BBzL"),s=t.n(o),u=t("1vPD"),c=t("52k5"),d=t("uMx8"),l=t("JUgE"),m=t("7FO1"),g=function(e){function Instructions(){return e.apply(this,arguments)||this}var t;return a()(Instructions,e),Instructions.prototype.render=function render(){var e=this.props,t=e.instructions,n=e.itemMetadata,a=e.labLauncher,r=e.learnerAssignment,o=n.get("course.id"),g=n.get("id"),p=Object(d.a)(o,g),h=n.getTypeName(),f=Object(d.b)(o,g),k="programming"===h,v=("gradedProgramming"===h||"ungradedProgramming"===h)&&"script"===r.submissionBuilderSchema.get("typeName"),b,T=!k&&!v&&!(f||a);return i.a.createElement("div",{className:"rc-Instructions c-programming-instructions bt3-row"},i.a.createElement("div",{className:"bt3-col-md-8"},i.a.createElement("div",{className:"c-programming-instructions-content"},t&&i.a.createElement(l.a,{cml:t.get("assignmentInstructions")}))),i.a.createElement("div",{className:"bt3-col-md-4"},p&&p.templateId&&i.a.createElement(m.a,{itemMetadata:n,templateId:p.templateId,itemId:g}),k&&i.a.createElement(u.a,{itemMetadata:n}),v&&i.a.createElement(c.a,{itemMetadata:n}),T&&i.a.createElement("div",{className:"well theme-light"},i.a.createElement("h3",{className:"c-title"},s()("How to submit")),i.a.createElement("p",null,s()('When you\'re ready to submit, you can upload files for each part of the assignment on the "My submission" tab.')))))},Instructions}(i.a.Component);e.a=g},kp6c:function(module,exports,e){},nJfZ:function(module,exports,e){},skzQ:function(module,exports){exports.default={"How to submit":"Как отправить","When you're ready to submit, you can upload files for each part":"Когда работа будет готова, вы можете загрузить файлы для каждой части","of the assignment on the \"My submission\" tab.":"задания на вкладке \"Моя работа\"."}},tOcQ:function(module,exports,e){var t=e("nJfZ"),n;"string"==typeof t&&(t=[[module.i,t,""]]);var a={transform:void 0},r=e("aET+")(t,a);t.locals&&(module.exports=t.locals)},uMx8:function(module,e,t){"use strict";t.d(e,"a",function(){return o}),t.d(e,"b",function(){return s});var n=t("MVZn"),a=t.n(n),r=t("KMW/"),i={templateId:"IIknfCCpTv2JJ3wgqU79KA"},o=function getSleuthConfig(e,t){var n,o=(r.a.get("Workspaces","sleuthAssignments")||[]).find(function(n){return n.courseId===e&&n.itemId===t});return o?a()({},i,o):null},s=function isSleuthAssignment(e,t){return!!o(e,t)}}}]);