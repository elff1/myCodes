<?php
$this->breadcrumbs = array (
		'Online Test Subsystem' => array (
				'/testOnline' 
		),
		'Course List' => array (
				'default/listCourses' 
		),
		AccountComponent::getSelected_course_name () => array (
				'paperBank/' 
		),
		'Take Test' 
);
$arr = $this->actionGetTimeLeft();
$tsec = $arr[1];
$reason = $arr[0];
$closeurl = $this->createUrl("userExit");
/*
 * TODO: 如何加入离开页面并去掉刷新事件
Yii::app()->clientscript->registerScript('userexit','
window.onbeforeunload = function() {$.ajax({
            url: "'.$closeurl.'",
            async : false,
        }); };');
        */
//$.get("'.$this->createUrl ( "getTimeLeft" ).'",function(data,textStatus)
Yii::app()->clientscript->registerScript('test-timer','
function updateTimer(data)
{

}

$(document).ready(function(){
			reason = '.$reason.';
			data = '.$tsec.';
			var res ="";
			reason = parseInt(reason);
			data = parseInt(data);
				if(reason >= -1)
				{
					if(reason == -1)
						res = "no time limit! enjoy yourself";
					else
					{
					var notice = $("#test-user-timer");
					if(reason < 0)
								{
									res = "Time limit exceeded!!!";
								}
								else
								{
									res = parseInt(data/3600)+":"+parseInt(data%3600/60)+":"+parseInt(data%60)+" remaining";
								}
								notice.text(res);
						setInterval(function()
						{
								data--;
								if(data < 0)
								{
									res = "Time limit exceeded!!!";
								}
								else
								{
									res = parseInt(data/3600)+":"+parseInt(data%3600/60)+":"+parseInt(data%60)+" remaining";
								}
								notice.text(res);
						}
						,1000);
					}
				}
				else if(reason == -5)
				{
					var notice = $("#test-user-timer");
					res = parseInt(data/3600)+":"+parseInt(data%3600/60)+":"+parseInt(data%60)+" remaining";
					notice.text(res);
				}
		}
	);
');
?>
<script type="text/javascript">


function checkAllDone(targetUrl,ajaxUrl)
{
	var msg = "Do you want to submit your test?";
	$.get(ajaxUrl,function(data,textStatus)
			{
				if(data == true)
					msg += " You haven't finish all your problems..."
				if(confirm(msg))
					window.location = targetUrl;
			}
	);
	return false;
}
</script>
<?php
$finishUrl = $this->createUrl ( 'finishTest' );
$ajaxUrl = $this->createUrl ( 'endTestCheck' );
$this->menu = array (
		array (
				'label' => 'Submit this test',
				'url' => "javascript:checkAllDone('$finishUrl','$ajaxUrl')" 
		// 'linkOptions' => array('onclick' => 'checkAllDone();'),
)
		,
		array (
				'label' => 'Back to other papers',
				'url' => array (
						'paperBank/' 
				) 
		) ,
		(!$this->suspendFlag)?array (
				'label' => 'Stop Ticking',
				'url' => array (
						'suspend' 
				) 
		):
		array (
				'label' => 'Resume ticking',
				'url' => array (
						'resume'
				)
		),
// array('label'=>'Delete TestRecording', 'url'=>'#',
// 'linkOptions'=>array('submit'=>array('delete','id'=>1),'confirm'=>'Are you
// sure you want to delete this item?'))
);
if (! $this->canSubmit)
	array_shift ( $this->menu );
?>

<h1>Attending Test</h1>
<div class="flash-notice" id="test-user-timer">
Oh no, I can't load time.
</div>
<div class="form">

<?php

$form = $this->beginWidget ( 'CActiveForm', array (
		'id' => 'test-recording-form',
		'enableAjaxValidation' => false 
		)
// 'action' => array('testRecording/judge')
 );
?>

<?php foreach($models as $i=>$model): ?>
<div class="view">
<?php $problem = $model->paperPro->pro;?>
	<p class="note">
			Fields with <span class="required">*</span> are required.
		</p>

	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo CHtml::encode($problem->getAttributeLabel('question')); ?>:</b>
		<?php echo CHtml::encode($problem->question); ?>
	</div>
		<div class="row">
		<?php echo $form->hiddenField($model,"[$i]paper_pro_id")?>
	</div>
		<div class="row">
	<?php echo $form->labelEx($model,'Select Your answer'); ?>
	<?php if($problem->type == QuestionBank::$CHOICE_TYPE) :?>
		<?php echo $form->radioButtonList($model,"[$i]choose",array('A'=>$problem->selection_a,'B'=>$problem->selection_b,'C'=>$problem->selection_c,'D'=>$problem->selection_d)); ?>
	<?php else:  ?>
		<?php echo $form->radioButtonList($model,"[$i]choose",array('T'=>('true'),'F'=>('false'))); ?>
	<?php endif; ?>
	<?php echo $form->error($model,"[$i]choose"); ?>
	</div>
	</div>
<?php endforeach; ?>
<?php

$this->widget ( 'CLinkPager', array (
		'pages' => $pages 
) )?>
	<div class="row buttons">
		<?php echo CHtml::submitButton('Save'); ?>
	</div>

<?php $this->endWidget(); ?>
</div>

<!-- form -->