<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'student-basic-info-form',
	'enableAjaxValidation'=>false,
	'enableClientValidation'=>true,
	'htmlOptions' => array('enctype' => 'multipart/form-data'),
)); ?>

	<p class="note"><?php
	echo InformationManagementModule::t('other','Fields with <span class="required">*</span> are required.'); /* no CHtml::encode here*/?></p>

	<?php echo $form->errorSummary(array($model,$personalInfoModel)); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'student_id'); ?>
		<?php echo $form->textField($model,'student_id',array('size'=>10,'maxlength'=>10)); ?>
		<?php echo $form->error($model,'student_id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'current_grade'); ?>
		<?php echo $form->textField($model,'current_grade',array('size'=>4,'maxlength'=>4)); ?>
		<?php echo $form->error($model,'current_grade'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'program_id'); ?>
		<?php echo $form->dropDownList($model,'program_id',Program::model()->programList); ?>
		<?php echo $form->error($model,'program_id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'entry_date'); ?>
		<?php $this->widget('zii.widgets.jui.CJuiDatePicker', array(  

        'attribute' => 'entry_date',  
        'model'=>$model,
        'options' => array(
                'dateFormat' => 'yy-mm-dd',  

        ),
		));?>
		<?php echo $form->error($model,'entry_date'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'class_id'); ?>
		<?php echo $form->dropDownList($model,'class_id',ClassBasicInfo::model()->classList); ?>
		<?php echo $form->error($model,'class_id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'remark'); ?>
		<?php echo $form->textField($model,'remark',array('size'=>60,'maxlength'=>256)); ?>
		<?php echo $form->error($model,'remark'); ?>
	</div>
	
	<?php echo $this->renderPartial('/personalInfo/_embeddedForm', array('personalInfoModel'=>$personalInfoModel,'form'=>$form)); 
	//so that every type of user can reuse this.
	?>

	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? Yii::t('base','Create'):Yii::t('base','Save')); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->